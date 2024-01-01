# Development
- Visual Studio 2022 is used for this project.
## Installing dependencies
1. Download the following libraries (VC version):
    - [SDL2](https://github.com/libsdl-org/SDL/releases)
    - [SDL_image](https://github.com/libsdl-org/SDL_image/releases/)
2. Extract the files and put them in a safe place.
3. Open VS project, press **Alt+F7**, click on **VC++ Directories**. Add your libraries path into indicated fields.
    ![](docs/1.png)
4. Find **Linker** > **Input**. Add your **\*.lib** files there.
    ![](docs/2.png)
5. Copy the SDL_image DLL file into your executable folder.
# Known issues
- Exception thrown: read access violation where `**std::_Tree<std::_Tset_traits<unsigned int,std::less<unsigned int>,std::allocator<unsigned int>,0> >::_Get_scary**(...)` returned `nullptr`. This starts from:
    ```cpp
    // object_system.cpp
    void ObjectSystem::update() {
        for (auto const& e : entities) {
            // TODO: returned nullptr
            auto& transform = game_manager.getComponent<Transform>(e);
            auto& sprites = game_manager.getComponent<Sprites>(e);
            transform.x++; transform.y++;
            sprites.dst.x++; sprites.dst.y++;
        }
    }
    ```