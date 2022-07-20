pipeline {
  agent {
    node {
      label 'windows-agent-02'
      customWorkspace "D:\\jenkins-workspace\\supremacy-gameclient"
    }
  }
  environment {
    runUAT = "C:\\Program Files\\Epic Games\\UE_5.0\\Engine\\Build\\BatchFiles\\RunUAT.bat"
    project = "${env.WORKSPACE}\\Supremacy.uproject"
    buildDir = "${env.WORKSPACE}\\Build"
    configFolder = "${env.WORKSPACE}\\Windows\\Supremacy\\Saved\\Config\\Windows"
    configFile= "${configfolder}\\Engine.ini"
    defaultEngineFile = "${env.WORKSPACE}\\Config\\DefaultEngine.ini"
    zip = "C:\\Program Files\\7-Zip\\7z.exe"
    buildZipPath = "D:\\supremacy-builds-zip\\${env.BRANCH_NAME}"
  }
  stages {
    stage('Build') {
      steps {
        echo 'Build stage started.'
        script {
          echo 'Get version'
          latestTag = bat(
                        returnStdout: true,
                        script: 'git describe --tags --always'
                      )
          env.VERSION = latestTag
        }
        echo 'Sending notification to Slack.'
        slackSend channel: '#test-notifications', 
          color: '#4A90E2',
          message: ":arrow_upper_right: *supremacy-gameclient* build has *started*. Version: ${env.VERSION}. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        
        bat """
            echo 'V8 library setup'
            setup.bat
            """ 
        echo 'Temporarily change default config to DX11 (fix UE5 crash)'
        bat """
            Config\\inifile ${defaultEngineFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
            Config\\inifile ${DefaultEngineFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11
            """

        bat "\"${runUAT}\" BuildCookRun -project=\"${project}\" -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory=\"${buildDir}\" -log Log=\"${env.WORKSPACE}\\Log.txt\""
        
        echo 'Revert default config back to DX12'
        bat """
            Config\\inifile ${configFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=
            Config\\inifile ${configFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11
            """
        
        echo "Create Config Folder and Engine.ini file if they don't exist"
        script {
          if (!fileExists("$configFile")) {
              bat """
                  mkdir ${configFolder}
                  type nul > ${configFile}
                  """
          } 
        }

        echo 'Setup local config to DX11'
        bat """
            Config\\inifile ${configFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
            Config\\inifile ${configFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11
            """

        echo 'Set version number'
        bat """
            Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] Version=${env.VERSION}
            Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] BuildBranch=${env.BRANCH_NAME}
	          Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] Hash=${env.GIT_COMMIT}
            """
        echo 'Build stage finished.'
      }
      post {
        success {
          echo 'Build stage successful.'
          slackSend channel: '#test-notifications',
            color: 'good', 
            message: ":white_check_mark: *supremacy-gameclient* build has *succeeded*. Version: ${env.VERSION}. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        }
        failure {
          echo 'Build stage unsuccessful.'
          slackSend channel: '#test-notifications',
          color: 'danger', 
          message: ":x: *supremacy-gameclient* build has *failed*. Version: ${env.VERSION}. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        }
      }
    }
    stage('Deploy'){
      steps {
        echo 'Deploy stage started.'
        bat "\"${zip}\" a ${buildZipPath}\\${env.GIT_COMMIT.take(7)}.zip ${buildDir}"
        bat "for %i in (${buildZipPath}\\*) do if not %~nxi == ${env.GIT_COMMIT.take(7)}.zip del %i"
        echo 'Deploy stage finished.'
      }
      post {
        success {
          echo 'Deploy stage successful.'
          slackSend channel: '#test-notifications',
            color: 'good', 
            message: ":white_check_mark: *supremacy-gameclient* deploy has *succeeded*. Version: ${env.VERSION}. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-deploy>"
        }
        failure {
          echo 'Deploy stage unsuccessful.'
          slackSend channel: '#test-notifications',
          color: 'danger', 
          message: ":x: *supremacy-gameclient* deploy has *failed*. Version: ${env.VERSION}. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-deploy>"
        }
      }
    }
  }
}
  