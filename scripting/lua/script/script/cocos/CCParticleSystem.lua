function cc.createParticle(parent, name, x, y, z, tag)
    local spark = CCParticleSystemQuad:create(R(name))
    spark:setPosition(x, y)
    if tolua.isa(parent, "Widget") then
        parent:addNode(spark, z, tag)
    else
        parent:addChild(spark, z, tag)
    end
    return spark
end