#include "framework/AssetManager.h"

#include <iostream>


namespace ly
{
    TUniquePtr<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager& AssetManager::Get()
    {
        if (assetManager == nullptr)
        {
            assetManager = TUniquePtr<AssetManager>{new AssetManager()};
        }
        return *assetManager;
    }

    TSharedPtr<sf::Texture> AssetManager::LoadTexture(const std::string& texturePath)
    {
        auto found = mLoadedTextureMap.find(texturePath);
        if (found != mLoadedTextureMap.end())
        {
            return found->second;
        }
        TSharedPtr<sf::Texture> newTexture{new sf::Texture};
        if (newTexture->loadFromFile(mRootDirectory + texturePath))
        {
            mLoadedTextureMap.insert({texturePath, newTexture});
            return newTexture;
        }
        return TSharedPtr<sf::Texture>{nullptr};
    }

    void AssetManager::CleanCycle()
    {
        for (auto iter = mLoadedTextureMap.begin();
             iter != mLoadedTextureMap.end();)
        {
            if (iter->second.use_count() == 1)
            {
                LY_LOG("Cleaning texture : %s...", iter->first.c_str());
                iter = mLoadedTextureMap.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void AssetManager::SetAssetRootDirectory(const std::string& directory)
    {
        mRootDirectory = directory;
    }

    AssetManager::AssetManager() : mRootDirectory{}
    {
    }
}
