function cc.createParticle(name, x, y, parent, tag, z)
    local spark = CCParticleSystemQuad:create(R(name))
    spark:setPosition(x, y)
    parent:addChild(spark, tag, z)
    return spark
end