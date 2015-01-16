function cc.createParticle(name, x, y, anchor, parent, tag)
    local spark = CCParticleSystemQuad:create(R(name))
    spark:setPosition(x,y)
    parent:addChild(spark, tag)
    return spark
end