--Vec3

function cc.V3(p1, p2, p3)
    return {x = p1, y = p2, z = p3}
end

function cc.V3Add(p1, p2)
    return {x = p1.x + p2.x, y = p1.y + p2.y, z = p1.z + p2.z}
end

function cc.V3Sub(p1, p2)
    return {x = p1.x - p2.x, y = p1.y - p2.y, z = p1.z - p2.z}
end

function cc.V3Mul(p1, p2)
    return {x = p1.x * p2.x, y = p1.y * p2.y, z = p1.z * p2.z}
end

function cc.V3Dot(p1, p2)
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z
end

function cc.V3MulEx(p1, p2)
    return {x = p1.x * p2, y = p1.y * p2, z = p1.z * p2}
end

function cc.V3LengthSquared(p)
    return (p.x * p.x + p.y * p.y + p.z * p.z)
end

function cc.V3Length(p)
    return math.sqrt(p.x * p.x + p.y * p.y + p.z * p.z)
end

function cc.V3Normalize(p)
    local n = p.x * p.x + p.y * p.y + p.z * p.z
    if n == 1.0 then return end
    
    n = math.sqrt(n);
    if n < 2e-37 then return end
    
    n = 1.0 / n;
    
    p.x = p.x * n
    p.y = p.y * n
    p.z = p.z * n
end
