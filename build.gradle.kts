plugins {
    kotlin("multiplatform") version "1.9.10"
}

group = "me.crazy"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

tasks.register<Copy>("copyDLL") {
    from("E:\\Games\\MFS SDK\\SimConnect SDK\\lib\\SimConnect.dll")
    into(layout.buildDirectory.dir("bin/native/debugExecutable/"))
}

kotlin {
    val hostOs = System.getProperty("os.name")
    val isMingwX64 = hostOs.startsWith("Windows")
    val nativeTarget = when {
        hostOs == "Mac OS X" -> macosX64("native")
        hostOs == "Linux" -> linuxX64("native")
        isMingwX64 -> mingwX64("native")
        else -> throw GradleException("Host OS is not supported in Kotlin/Native.")
    }

    nativeTarget.apply {
        val main by compilations.getting {
            dependencies {
                implementation("org.jetbrains.kotlinx:kotlinx-io-core:0.3.0") // Native
            }
        }
        val simconnect by main.cinterops.creating {
            defFile("src/nativeInterop/cinterop/simconnect.def")
            compilerOpts("-IC:\\Users\\Crazy\\IdeaProjects\\msfs")
        }
        binaries {
            executable {
                entryPoint = "main"
            }
        }
    }
    sourceSets {
        val nativeMain by getting
        val nativeTest by getting
    }
}
