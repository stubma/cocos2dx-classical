function cc.createParticle(parent, name, x, y, z, tag)
    local spark = CCParticleSystemQuad:create(R(name))
    spark:setPosition(x, y)
    parent:addChild(spark, z, tag)
    return spark
end