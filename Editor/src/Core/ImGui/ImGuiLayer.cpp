#include "ImGuiLayer.h"

#include "Application.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

#ifdef ED_WINDOW_SDL3
#include <imgui_impl_sdl3.h>
#endif

#include <SDL3/SDL.h>

namespace Editor {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// --- ImGui Init ---
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.Fonts->AddFontFromFileTTF((std::string(ASSETS_PATH) + "Fonts/JetBrainsMono-Bold.ttf").c_str());

		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init("#version 460");

		// Init ImGui Window & Context
#ifdef ED_WINDOW_SDL3
		bool task = ImGui_ImplSDL3_InitForOpenGL(
			static_cast<SDL_Window*>(Application::Get()->GetWindow()->GetNativeWindow()),
			static_cast<SDL_GLContext>(Application::Get()->GetWindow()->GetNativeContext())
		);

		ED_ASSERT(task, "Failed To Init SDL3 Context & Window For ImGui");
#endif

		// Custom Style
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1333f, 0.1333f, 0.1333f, 1.0f);

		ED_LOG_WARN("||---> ImGui Initialized <---||");
	}

	void ImGuiLayer::OnDeatch()
	{
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto appWindow = Application::Get()->GetWindow();
		io.DisplaySize = ImVec2(appWindow->GetWidth(), appWindow->GetHeight());

		ImGui_ImplOpenGL3_NewFrame();
#ifdef ED_WINDOW_SDL3	// If The Window from SDL3
		ImGui_ImplSDL3_NewFrame();
#endif
		ImGui::NewFrame();

		// Docking Space
		
		// TL;DR; this demo is more complicated than what most users you would normally use.
	// If we remove all options we are showcasing, this demo would become a simple call to ImGui::DockSpaceOverViewport() !!
	// In this specific demo, we are not using DockSpaceOverViewport() because:

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = /*ImGuiWindowFlags_MenuBar |*/ ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		{
			window_flags |= ImGuiWindowFlags_NoBackground;
		}

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", nullptr, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		// REMINDER: THIS IS A DEMO FOR ADVANCED USAGE OF DockSpace()!
		// MOST REGULAR APPLICATIONS WILL SIMPLY WANT TO CALL DockSpaceOverViewport(). READ COMMENTS ABOVE.
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		ImGui::End();

		// Titlebar
		TitleBar(nullptr);

	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			
			auto currentWindow = Application::Get()->GetWindow();

			// ReMake Context For Update ImGui Docking Viewports
#ifdef ED_WINDOW_SDL3
			SDL_GL_MakeCurrent(static_cast<SDL_Window*>(currentWindow->GetNativeWindow()), static_cast<SDL_GLContext>(currentWindow->GetNativeContext()));
#endif
		}
	}

	void ImGuiLayer::TitleBar(bool* pAppClose)
	{

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.f, 14.f));

		if (ImGui::BeginMainMenuBar())
		{

			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("FFF"))
				{
					ImGui::EndTabItem();
				}


				ImGui::EndMenu();
			}

			// Title
			ImGui::SameLine((ImGui::GetWindowWidth() / 2) - 30.f);
			ImGui::Text(Application::Get()->GetWindow()->GetProperties().Title.c_str());

			ImGui::SameLine(ImGui::GetWindowWidth() - 44.f);

			/*if (ImGui::ImageButton("&&", (ImTextureRef)tex.GetID(), ImVec2(20.f, 20.f)))
			{
				*pAppClose = false;
			}

			ImGui::SameLine(ImGui::GetWindowWidth() - 80.f);
			if (ImGui::ImageButton("&77", (ImTextureRef)tex_2.GetID(), ImVec2(20.f, 20.f)))
			{
				printf("Out\n");
			}*/

		}
		ImGui::EndMainMenuBar();
		ImGui::PopStyleVar();


		if (ImGui::Begin("Editor Styal"))
			ImGui::ShowStyleEditor();
		ImGui::End();

	}

}