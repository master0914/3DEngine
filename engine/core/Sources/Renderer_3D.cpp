//
// Created by Master0914 on 01.09.2025.
//
#include "../Header/Renderer_3D.h"

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
                mat4 mvpMatrix = viewModel * camera->getProjectionMatrix();

                std::cout << "View * Model:\n" << viewModel << std::endl;
                std::cout << "Final MVP:\n" << mvpMatrix << std::endl;

                std::cout << "projection: \n" << camera->getProjectionMatrix() << "View: \n" << camera->getViewMatrix() << "transform: \n" << command.transform << "\n";
                std::cout << "MVP: \n" <<mvpMatrix;

                rasterizeMesh(*command.mesh, mvpMatrix);
            }
        };

        void Renderer_3D::setCamera(Camera &camera){
            this->camera = &camera;
        };

        void Renderer_3D::rasterizeMesh(const Mesh& mesh, const mat4& mvpMatrix) {
            // rasterizing (Bitte.. geh endlich!!)
            const std::vector<Triangle>& meshTriangles = mesh.getTriangles();
            std::cout << "rasterizing start \n";
            for (const Triangle& triangle : meshTriangles) {
                std::cout << triangle << "\n";
                //triangle.debugPrint();
                // transformiert alle 3 vertices mit der mvpMatrix
                vec4 vertices[3];
                for (int i = 0; i < 3; ++i) {
                    // Konvertiere Vertex-Position zu vec4 (homogene Koordinaten)
                    vec3 pos = triangle.vertices[i].position;
                    vertices[i] = mvpMatrix * vec4(pos.getX(), pos.getY(), pos.getZ(), 1.0f);
                }
                std::cout << "vertices to vec4 translated \n";
                std::cout << "vertices after transformation: \n" << vertices[0] << "\n" << vertices[1] << "\n"<< vertices[2] << "\n";
                // führ den perspective divide durch (x/w, y/w, z/w)
                for (vec4& vertex : vertices) {
                    // fuck nicht durch null teilen
                    if (std::abs(vertex.w) < 1e-6f) {
                        vertex.w = 1e-6f;
                    }
                    float w_inv = 1.0f / vertex.w;
                    std::cout << "vertex: " << vertex;

                    vertex.x *= w_inv;
                    vertex.y *= w_inv;
                    vertex.z *= w_inv; // Tiefeninformation für Z-Buffer
                    vertex.w = 1.0f;  // Speichere 1/w für perspektivisch korrekte Interpolation (später)
                    std::cout << "\n after division by " << (1.0f / w_inv) <<"\n" << vertex << "\n";
                }
                std::cout << "vertices divided with w \n";

                // führt clipping durch
                //@TODO Clipping
                // mappe die homogenen Koordinaten (-1 to 1) auf Screen-Koordinaten (0 to width/height) um
                vec3 screenCoords[3];
                for (int i = 0; i < 3; ++i) {
                    screenCoords[i].x = (vertices[i].x + 1.0f) * 0.5f * m_width;
                    screenCoords[i].y = (1.0f - vertices[i].y) * 0.5f * m_height; // Y ist invertiert
                    screenCoords[i].z = vertices[i].z; // Behalte Z für Depth-Testing
                }
                std::cout << "Screecoords: " << "\n" << screenCoords[0]  << "\n" << screenCoords[1]  << "\n" << screenCoords[2] << "\n";
                // - Rasterisiere das Dreieck (deine draw_triangle Funktion)
                renderer2D.drawTriangleWireFrame(m_FrameBuffer,m_width,m_height,screenCoords[0], screenCoords[1], screenCoords[2], renderColor);
                //   Übergib dabei die transformierten Koordinaten und den Z-Wert für den Depth-Test
            }
        }

        void Renderer_3D::clearBuffer() {
            std::fill(m_FrameBuffer.begin(), m_FrameBuffer.end(), backGroundColor); // Schwarzer Hintergrund
            std::fill(m_DepthBuffer.begin(), m_DepthBuffer.end(), 1.0f);       // Maximaler Tiefenwert
        }

}
