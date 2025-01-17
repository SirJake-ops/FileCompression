#include <iostream>
#include "imgui.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "FileManipulation/LoadData.h"
#include "external/ImGuiFileDialog/ImGuiFileDialog.h"
#include <GLFW/glfw3.h>
#include <memory>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

void LoadDataOperationsServices(std::unique_ptr<LoadData>& loadData, const std::string& fileName, const std::string& filePath) {
    loadData->readCompressedFile(fileName, filePath);
}


int main(int argc, char *argv[]) {
    std::cout << "Still works!" << std::endl;
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "ImGui Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool uploadComplete = false;
    bool isUploading = false;
    bool showFileDialog = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Text("File Upload/Download");

        if (ImGui::Button("Upload")) {
            showFileDialog = true;
            isUploading = true;
        }

        if (showFileDialog) {
            //Here we open a dialog to choose a file that we will support for compression. So far thinking it will only be media file types, mostly if not all video files.
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File",
                                                    ".mp4,.avi,.mkv,.mov,.flv,.wmv,.webm,.png,.jpg,.jpeg,.bmp,.gif,.tiff,.pdf,.doc,.docx,.xls,.xlsx,.ppt,.pptx,.txt,.csv,.zip,.rar,.7z,.tar,.gz,.iso");
            showFileDialog = false;
        }


        if (isUploading) {
            ImGui::Text("Uploading... Please wait.");
        }

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
            std::string filePathName;
            std::string filePath;
            if (ImGuiFileDialog::Instance()->IsOk()) {
                filePathName = ImGuiFileDialog::Instance()->GetCurrentFileName();
                filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                isUploading = true;
            }
            std::unique_ptr<LoadData> fileLoad = std::make_unique<LoadData>(filePathName, filePath);
            LoadDataOperationsServices(fileLoad, filePathName, filePath);
            ImGuiFileDialog::Instance()->Close();
            uploadComplete = true;
            isUploading = false;
        }

        if (uploadComplete) {
            if (ImGui::Button("Download")) {
                std::cout << "Download initiated.\n";
                uploadComplete = false;
            }
        } else {
            ImGui::BeginDisabled();
            ImGui::Button("Download");
            ImGui::EndDisabled();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}