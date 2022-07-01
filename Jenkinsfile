pipeline {
  agent {
    node {
      label 'windows-agent-01'
      customWorkspace "C:\\Users\\Ninja\\Documents\\supremacy-gameclient-ci-workspace"
    }
  }
  environment {
    runUAT = "C:\\Program Files\\Epic Games\\UE_5.0\\Engine\\Build\\BatchFiles\\RunUAT.bat"
    project = "${env.WORKSPACE}\\Supremacy.uproject"
    buildPath = "${env.WORKSPACE}\\Build"
    configFile= "${buildPath}\\Windows\\Supremacy\\Saved\\Config\\Windows\\Engine.ini"
    defaultEngineFile = "${env.WORKSPACE}\\Config\\DefaultEngine.ini"
    v8path = "${env.WORKSPACE}"
    verison = """${bat(
                  returnStdout: true,
                  script: 'git describe --tags'
              )}"""
    hash = """${bat(
                  returnStdout: true,
                  script: 'git rev-parse --verify HEAD'
              )}"""
  }
  stages {
    stage('Building') {
      steps {
        echo 'Build stage started.'
        echo 'Sending notification to Slack.'
        // slackSend channel: '#ops-deployment', 
        //   color: '#4A90E2',
        //   message: "Build ${env.BUILD_NUMBER} has started at node ${env.NODE_NAME}..."

        bat "Config\\inifile ${defaultEngineFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0"
        bat "Config\\inifile ${DefaultEngineFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11"

        bat """
            echo 'V8 library setup'
            setup.bat
            """ 
        
        bat "\"${runUAT}\" BuildCookRun -project=\"${project}\" -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory=\"${buildPath}\""
        
        bat "Config\\inifile ${configFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0"
        bat "Config\\inifile ${configFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11"

        bat "Config\\inifile ${defaultEngineFile} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12="
        bat "Config\\inifile ${defaultEngineFile} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX12"

        bat "Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] Version=${version}"
        bat "Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] BuildBranch=${env.BRANCH_NAME}"
	      bat "Config\\inifile ${configFile} [/Game/UI/HUD.HUD_C] Hash=${hash}"

        echo "BuildNo ${verison} Branch ${env.BRANCH_NAME} Hash ${hash}"
      }
      post {
        success {
          echo 'Build stage successful.'
        //   slackSend channel: '#ops-deployment',
        //     color: 'good', 
        //     message: "*${currentBuild.currentResult}:* Build ${env.BUILD_NUMBER} has *succeded!* :innocent:"
        }
        failure {
          echo 'Build stage unsuccessful.'
        // slackSend channel: '#ops-deployement',
        //   color: 'danger', 
        //   message: "*${currentBuild.currentResult}:* Build ${env.BUILD_NUMBER} has *failed* :astonished:"
        }
      }
    }
  }
}
  