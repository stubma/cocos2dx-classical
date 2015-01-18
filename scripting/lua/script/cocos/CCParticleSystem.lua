function cc.createParticle(name, x, y, parent, z, tag)
    local spark = CCParticleSystemQuad:create(R(name))
    spark:setPosition(x, y)
    parent:addChild(spark, z, tag)
    return spark
end