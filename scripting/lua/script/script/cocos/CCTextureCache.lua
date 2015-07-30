function cc.removeTexture(name)
    CCTextureCache:sharedTextureCache():removeTextureForKey(R(name));
end