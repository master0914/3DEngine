//
// Created by Master0914 on 01.09.2025.
//
#include "../Header/renderer_3D.h"
#include "../Header/debug.h"
#include <chrono>
#include <thread>


namespace Engine{
        Renderer_3D::Renderer_3D(Engine::Window &window) {
            m_width = window.getWidth();
            m_height = window.getHeight();

            backGroundColor = 0xff000000;
            renderColor = 0xffff0000;

            // Framebuffer für Farbwerte initialisieren
            m_FrameBuffer.resize(m_width * m_height);

            // Z-Buffer initialisieren (jeder Wert startet mit der maximalen Tiefe)
            m_DepthBuffer.resize(m_width * m_height, 1.0f);

            this->window = &window;
        }

        void Renderer_3D::beginFrame() {
            m_RenderQueue.clear();
            clearBuffer();
            window->Clear();
        };

        void Renderer_3D::submit(const Mesh &mesh, const mat4 &transform){
            m_RenderQueue.push_back({&mesh, transform});
        };

        void Renderer_3D::present() {
            window->DrawPixelArray(m_FrameBuffer);
            window->Present();
        }

        void Renderer_3D::endFrame(){
            // In Renderer_3D::endFrame()
            if (camera == nullptr) {
                std::cerr << "ERROR: Camera is null! Call setCamera() first." << std::endl;
                return; // Beende die Funktion vorzeitig
            }
            for(RenderCommand& command: m_RenderQueue){
                //MVP-Matrix:
                //Model: command.transform
                //View: camera.getViewMatrix
                //Projection: camera.getProjectionMatrix
                //mat4 mvpMatrix = camera->getProjectionMatrix() * (camera->getViewMatrix() * command.transform);
                mat4 viewModel = camera->getViewMatrix() * command.transform;
                mat4 mvpMatrix = camera->getProjectionMatrix() * viewModel;
//                Testing MVP multiplication
//                 DEBUG_PRINT("View * Model:\n" << viewModel << std::endl);
//                 DEBUG_PRINT("Final MVP:\n" << mvpMatrix << std::endl);
//
//                 DEBUG_PRINT("projection: \n" << camera->getProjectionMatrix() << "View: \n" << camera->getViewMatrix() << "transform: \n" << command.transform << "\n");
//                 DEBUG_PRINT("MVP: \n" <<mvpMatrix);

                rasterizeMesh(*command.mesh, mvpMatrix);
            }
        };

        void Renderer_3D::setCamera(Camera &Camera){
            this->camera = &Camera;
        };

        void Renderer_3D::rasterizeMesh(const Mesh& mesh, const mat4& mvpMatrix) {
            // rasterizing (Bitte.. geh endlich!!)
            const std::vector<Triangle>& meshTriangles = mesh.getTriangles();
            DEBUG_PRINT("rasterizing start \n");
            int i = 0;
            for (const Triangle& triangle : meshTriangles) {

                DEBUG_PRINT(i << ":   "<<triangle << "\n");

//                window->PollEvents();
//                window->Clear();
//                m_FrameBuffer.clear();
//                m_FrameBuffer.resize(m_width * m_height);

                // transformiert alle 3 vertices mit der mvpMatrix
                vec4 vertices[3];
                for (int i = 0; i < 3; ++i) {
                    // Konvertiere Vertex-Position zu vec4 (homogene Koordinaten)
                    vec3 pos = triangle.vertices[i].position;
                    vertices[i] = mvpMatrix * vec4(pos.getX(), pos.getY(), pos.getZ(), 1.0f);
                }
                DEBUG_PRINT("vertices to vec4 translated \n");
                DEBUG_PRINT("vertices after transformation: \n" << vertices[0] << "\n" << vertices[1] << "\n"<< vertices[2] << "\n");

                // führ den perspective divide durch (x/w, y/w, z/w)
                DEBUG_PRINT("Starting pespective divide: \n");
                for (vec4& vertex : vertices) {
                    // fuck nicht durch null teilen
                    if (std::abs(vertex.w) < 1e-6f) {
                        vertex.w = 1e-6f;
                    }
                    float w_inv = 1.0f / vertex.w;
                    DEBUG_PRINT("vertex: " << vertex);

                    vertex.x *= w_inv;
                    vertex.y *= w_inv;
                    vertex.z *= w_inv; // Tiefeninformation für Z-Buffer
                    vertex.w = 1.0f;  // Speichere 1/w für perspektivisch korrekte Interpolation (später)
                    DEBUG_PRINT("\n after division by " << (w_inv) <<"\n" << vertex << "\n");
                }
                DEBUG_PRINT("vertices divided with w \n");

                // führt clipping durch
                //@TODO Clipping
                // mappe die homogenen Koordinaten (-1 to 1) auf Screen-Koordinaten (0 to width/height) um
                vec3 screenCoords[3];
                for (int i = 0; i < 3; ++i) {
                    screenCoords[i].x = (vertices[i].x + 1.0f) * 0.5f * m_width;
                    screenCoords[i].y = (1.0f - vertices[i].y) * 0.5f * m_height; // Y ist invertiert
                    screenCoords[i].z = vertices[i].z; // Behalte Z für Depth-Testing
                }
                DEBUG_PRINT("Screecoords: \n" << screenCoords[0]  << "\n" << screenCoords[1]  << "\n" << screenCoords[2] << "\n");
                // - Rasterisiere das Dreieck (deine draw_triangle Funktion)
                std::cout << "drawing wireframe from triangle " <<   i << "\n";
                renderer2D.drawTriangleWireFrame(m_FrameBuffer,m_width,m_height,screenCoords[0], screenCoords[1], screenCoords[2], renderColor);
                //   Übergib dabei die transformierten Koordinaten und den Z-Wert für den Depth-Test


                // für testen eines dreiecks auskommentierer:
                // return;
//                present();
//                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                ++i;
            }
        }

        void Renderer_3D::clearBuffer() {
            std::fill(m_FrameBuffer.begin(), m_FrameBuffer.end(), backGroundColor); // Schwarzer Hintergrund
            std::fill(m_DepthBuffer.begin(), m_DepthBuffer.end(), 1.0f);       // Maximaler Tiefenwert
        }

}
