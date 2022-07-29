@Library("shared-library") _
pipeline {
  agent {
    node {
      label 'windows-agent-02'
      customWorkspace "D:\\jenkins-workspace\\supremacy-gameclient"
    }
  }
  environment {
    RUNUAT = "C:\\Program Files\\Epic Games\\UE_5.0\\Engine\\Build\\BatchFiles\\RunUAT.bat"
    PROJECT = "${env.WORKSPACE}\\Supremacy.uproject"
    BUILD_DIR = "${env.WORKSPACE}\\Build"
    CONFIG_FOLDER = "${BUILD_DIR}\\Windows\\Supremacy\\Saved\\Config\\Windows"
    CONFIG_FILE = "${CONFIG_FOLDER}\\Engine.ini"
    DEFAULT_ENGINE_FILE = "${env.WORKSPACE}\\Config\\DefaultEngine.ini"
    ZIP_EXE = "C:\\Program Files\\7-Zip\\7z.exe"
    ZIP_FOLDER = "D:\\supremacy-builds-zip"
    SH_EXE = "C:\\Program Files\\Git\\bin\\sh.exe"

  }
  stages {
    stage('Cancel previous builds') {
      steps {
        script {
          cancelPreviousBuilds()
        }
      }
    }
    stage('Build') {
      steps {
        echo 'Build stage started.'
        slackSend channel: '#test-notifications', 
          color: '#4A90E2',
          message: ":arrow_upper_right: *supremacy-gameclient* build has *started*. Commit: *${env.GIT_COMMIT.take(8)}*. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        
        echo 'Setup V8'
        script {
          if (!fileExists("${env.WORKSPACE}\\Plugins\\UnrealJs\\ThirdParty\\v8\\lib\\Win64\\Release\\v8_init.lib ")){
            bat """
                  setlocal
                  cd "${env.WORKSPACE}\\Plugins\\UnrealJs"
                  "$SH_EXE" install-v8-libs.sh
                  endlocal
                """
          }
        }
       
        echo 'Temporarily change default config to DX11 (fix UE5 crash)'
        bat """
            Config\\inifile ${DEFAULT_ENGINE_FILE} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
            Config\\inifile ${DEFAULT_ENGINE_FILE} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11
            """

        bat """
            "${RUNUAT}" BuildCookRun -project="${PROJECT}" -targetplatform=Win64 -clientconfig=Development -cook -build -stage -pak -archive -archivedirectory="${BUILD_DIR}"
            """
        
        echo 'Revert default config back to DX12'
        bat """
            Config\\inifile ${DEFAULT_ENGINE_FILE} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=
            Config\\inifile ${DEFAULT_ENGINE_FILE} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX12
            """
        
        echo "Create Config Folder and Engine.ini file if they don't exist"
        script {
          if (!fileExists("$CONFIG_FILE")) {
              bat """
                  mkdir ${CONFIG_FOLDER}
                  type nul >${CONFIG_FILE}
                  """
          } 
        }

        echo 'Setup local config to DX11'
        bat """
            Config\\inifile ${CONFIG_FILE} [/Script/Engine.RendererSettings] r.Nanite.RequireDX12=0
            Config\\inifile ${CONFIG_FILE} [/Script/WindowsTargetPlatform.WindowsTargetSettings] DefaultGraphicsRHI=DefaultGraphicsRHI_DX11
            """

        echo 'Set version number'
        bat """
            Config\\inifile ${CONFIG_FILE} [/Game/UI/HUD.HUD_C] Version=${SUPREMACY_VERSION}
            Config\\inifile ${CONFIG_FILE} [/Game/UI/HUD.HUD_C] BuildBranch=${env.BRANCH_NAME}
	          Config\\inifile ${CONFIG_FILE} [/Game/UI/HUD.HUD_C] Hash=${env.GIT_COMMIT}
            """
        echo 'Build stage finished.'
      }
      post {
        success {
          echo 'Build successful.'
          slackSend channel: '#test-notifications',
            color: 'good', 
            message: ":white_check_mark: *supremacy-gameclient* build has *succeeded*. Commit: *${env.GIT_COMMIT.take(8)}*. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        }
        failure {
          echo 'Build unsuccessful.'
          slackSend channel: '#test-notifications',
          color: 'danger', 
          message: ":x: *supremacy-gameclient* build has *failed*. Commit: *${env.GIT_COMMIT.take(8)}*. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-build>"
        }
      }
    }
    stage('Deploy'){
      steps {
        echo 'Deploy staging started.'
        bat "\"${ZIP_EXE}\" a ${ZIP_FOLDER}\\${env.GIT_COMMIT.take(8)}.zip ${BUILD_DIR}"
        echo 'Deploy stage finished.'
      }
      post {
        success {
          echo 'Deploy successful.'
          slackSend channel: '#test-notifications',
            color: 'good', 
            message: ":white_check_mark: *supremacy-gameclient* deploy has *succeeded*. Commit: *${env.GIT_COMMIT.take(8)}*. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-deploy>"
        }
        failure {
          echo 'Deploy unsuccessful.'
          slackSend channel: '#test-notifications',
          color: 'danger', 
          message: ":x: *supremacy-gameclient* deploy has *failed*. Commit: *${env.GIT_COMMIT.take(8)}*. Job name: *${env.JOB_NAME}*. Build no: *${env.BUILD_NUMBER}*. More info: <${env.BUILD_URL}|supremacy-gameclient-deploy>"
        }
      }
    }
  }
}
  