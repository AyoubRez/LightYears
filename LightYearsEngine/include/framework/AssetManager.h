#pragma once
#include "Core.h"
#include "SFML/Graphics/Texture.hpp"


namespace ly
{
    class AssetManager
    {
    public:
        static AssetManager& Get();
        TSharedPtr<sf::Texture> LoadTexture(const std::string& texturePath);
        void CleanCycle();
        void SetAssetRootDirectory(const std::string& directory);

    protected:
        AssetManager();

    private:
        static TUniquePtr<AssetManager> assetManager;
        TDictionary<std::string, TSharedPtr<sf::Texture>> mLoadedTextureMap;
        std::string mRootDirectory;
    };
}
