pipeline {
  agent {
    node {
      label 'windows-agent-02'
      customWorkspace "D:\\jenkins-workspace"
    }
  }
  environment {
    runUAT = "C:\\Program Files\\Epic Games\\UE_5.0\\Engine\\Build\\BatchFiles\\RunUAT.bat"
    project = "${env.WORKSPACE}\\Supremacy.uproject"
    buildPath = "${env.WORKSPACE}\\Build"
    configFile= "${buildPath}\\Windows\\Supremacy\\Saved\\Config\\Windows\\Engine.ini"
    defaultEngineFile = "${env.WORKSPACE}\\Config\\DefaultEngine.ini"
    v8path = "${env.WORKSPACE}"
    version = """${bat(
                  returnStdout: true,
                  script: 'git describe --tags --always'
              )}"""
    zip = "C:\\Program Files\\7-Zip\\7z.exe"
    buildZipPath = "D:\\supremacy-builds-zip\\${env.BRANCH_NAME}"
  }
  stages {
    stage('Build') {
      steps {
        echo 'Build stage started.'
        echo 'Sending notification to Slack.'
        slackSend channel: '#test-notifications', 
          color: '#4A90E2',
          message: "Started *supremacy-gameclient* build. Version: ${version}. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"

        bat "Config\\inifile ${defaultEngineFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0"
        bat "Config\\inifile ${DefaultEngineFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11"

        bat """
            echo 'V8 library setup'
            setup.bat
            """ 
        
        bat "\"${runUAT}\" BuildCookRun -project=\"${project}\" -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory=\"${buildPath}\" -log Log=\"${env.WORKSPACE}\\Log.txt\""
        
        bat "Config\\inifile ${configFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0"
        bat "Config\\inifile ${configFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11"

        bat "Config\\inifile ${defaultEngineFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12="
        bat "Config\\inifile ${defaultEngineFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX12"

        bat "Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] Version=${version}"
        bat "Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] BuildBranch=${env.BRANCH_NAME}"
	      bat "Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] Hash=${env.GIT_COMMIT}"

        echo 'Build stage finished.'
      }
      post {
        success {
          echo 'Build stage successful.'
          slackSend channel: '#test-notifications',
            color: 'good', 
            message: "*${currentBuild.currentResult}:* *supremacy-gameclient* build has *succeded* :innocent:. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        }
        failure {
          echo 'Build stage unsuccessful.'
          slackSend channel: '#test-notifications',
          color: 'danger', 
          message: "*${currentBuild.currentResult}:* *supremacy-gameclient* build has *failed* :astonished:. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        }
      }
    }
    stage('Deploy'){
      steps {
        echo 'Deploy stage started.'
        bat "\"${zip}\" a ${buildZipPath}\\${env.GIT_COMMIT.take(7)}.zip ${buildPath}"
        echo 'Deploy stage finished.'

    }
    post {
        success {
          echo 'Deploy stage successful.'
          slackSend channel: '#test-notifications',
            color: 'good', 
            message: "*${currentBuild.currentResult}:* *supremacy-gameclient* deploy has *succeded* :innocent:. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-deploy>"
        }
        failure {
          echo 'Deploy stage unsuccessful.'
          slackSend channel: '#test-notifications',
          color: 'danger', 
          message: "*${currentBuild.currentResult}:* *supremacy-gameclient* deploy has *failed* :astonished:. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-deploy>"
        }
      }
  }
}
  