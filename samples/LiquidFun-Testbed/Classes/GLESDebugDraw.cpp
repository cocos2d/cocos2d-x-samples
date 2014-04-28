/*
 * Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
 *
 * iPhone port by Simon Oliver - http://www.simonoliver.com - http://www.handcircus.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "GLESDebugDraw.h"
#include "cocos2d.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef WIN32
#include <alloca.h>
#endif

USING_NS_CC;

float currentscale = 1;	// amount of pixels that corresponds to one world unit, needed to use glPointSize correctly

GLESDebugDraw::GLESDebugDraw()
    : mRatio( 1.0f )
    , mPointSizeLocation(-1)
    , mColorLocation(-1)

{
    this->initShader();
}

GLESDebugDraw::GLESDebugDraw( float32 ratio )
    : mRatio( ratio )
    , mPointSizeLocation(-1)
    , mColorLocation(-1)
{
    this->initShader();
}

void GLESDebugDraw::initShader( void )
{
    mShaderProgram = ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
    mPointSizeLocation = mShaderProgram->getUniformLocation("u_pointSize");
    mColorLocation = mShaderProgram->getUniformLocation("u_color");
}

void GLESDebugDraw::DrawPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    b2Vec2* vertices = (b2Vec2*) alloca(sizeof(b2Vec2) * vertexCount);
    for( int i=0;i<vertexCount;i++) 
    {
        vertices[i] = old_vertices[i];
        vertices[i] *= mRatio;
    }

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);

//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);

    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,vertexCount);


    CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawFlatPolygon(const b2Vec2* old_vertices, int32 vertexCount, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    b2Vec2* vertices = (b2Vec2*) alloca(sizeof(b2Vec2) * vertexCount);
    for( int i=0;i<vertexCount;i++) {
        vertices[i] = old_vertices[i];
        vertices[i] *= mRatio;
    }

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);


    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,vertexCount);
}


void GLESDebugDraw::DrawSolidPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    b2Vec2* vertices = (b2Vec2*) alloca(sizeof(b2Vec2) * vertexCount);
    for( int i=0;i<vertexCount;i++) {
        vertices[i] = old_vertices[i];
        vertices[i] *= mRatio;
    }

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);

    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);

    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(2,vertexCount*2);

    CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    const float32 k_segments = 16.0f;
    int vertexCount=16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;

    GLfloat* glVertices = (GLfloat*) alloca(sizeof(GLfloat) * vertexCount * 2);
    for (int i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertices[i*2]=v.x * mRatio;
        glVertices[i*2+1]=v.y * mRatio;
        theta += k_increment;
    }
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);

    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,vertexCount);

    CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    const float32 k_segments = 16.0f;
    int vertexCount=16;
    const float32 k_increment = 2.0f * b2_pi / k_segments;
    float32 theta = 0.0f;
    
    GLfloat* glVertices = (GLfloat*) alloca(sizeof(GLfloat) * vertexCount * 2);
    for (int i = 0; i < k_segments; ++i)
    {
        b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
        glVertices[i*2]=v.x * mRatio;
        glVertices[i*2+1]=v.y * mRatio;
        theta += k_increment;
    }
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r*0.5f, color.g*0.5f, color.b*0.5f, 0.5f);

    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);

    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    // Draw the axis line
    DrawSegment(center,center+radius*axis,color);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(2,vertexCount*2);

    CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    GLfloat    glVertices[] =
    {
        p1.x * mRatio, p1.y * mRatio,
        p2.x * mRatio, p2.y * mRatio
    };
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);

    glDrawArrays(GL_LINES, 0, 2);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,2);

    CHECK_GL_ERROR_DEBUG();
}

float smoothstep(float x) { return x * x * (3 - 2 * x); }

void GLESDebugDraw::DrawParticles(const b2Vec2 *centers_old, float32 radius, const b2ParticleColor *colors, int32 count)
{
    /*
     // normally this is how we'd enable them on desktop OpenGL,
     // but for some reason this is not applying textures, so we use alpha instead
     glEnable(GL_POINT_SPRITE);
     glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
     */
    const float particle_size_multiplier = 8;  // no falloff
    const float global_alpha = 0.35f;  // instead of texture

    mShaderProgram->setUniformLocationWith1f(mPointSizeLocation, radius * mRatio * particle_size_multiplier);

    GL::blendFunc(GL_SRC_ALPHA, GL_ONE);

    b2Vec2 *centers = (b2Vec2 *) alloca(sizeof(b2Vec2) * count);
    for(int i=0; i<count; i++) {
        centers[i].x = centers_old[i].x *mRatio;
        centers[i].y = centers_old[i].y *mRatio;
    }

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, centers);
    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 0, 0, 1, 1);

	if (0 /*colors*/)
	{
        // hack to render with proper alpha on desktop for Testbed
        b2ParticleColor * mcolors = const_cast<b2ParticleColor *>(colors);
        for (int i = 0; i < count; i++)
        {
            mcolors[i].a = static_cast<uint8>(global_alpha * 255);
        }
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, &colors[0].r);
	}
	else
	{
        glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, 1, 1, 1, global_alpha);
        mShaderProgram->setUniformLocationWith4f(mColorLocation, 1, 1, 1, global_alpha);
	}

	glDrawArrays(GL_POINTS, 0, count);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,count);
}


void GLESDebugDraw::DrawTransform(const b2Transform& xf)
{
    b2Vec2 p1 = xf.p, p2;
    const float32 k_axisScale = 0.4f;
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    DrawSegment(p1, p2, b2Color(1,0,0));

    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    DrawSegment(p1,p2,b2Color(0,1,0));
}

void GLESDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    GLfloat                glVertices[] = {
        p.x * mRatio, p.y * mRatio
    };

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);

//    mShaderProgram->setUniformLocationWith1f(mPointSizeLocation, s_pointSize);

    glDrawArrays(GL_POINTS, 0, 1);


    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,1);

    CHECK_GL_ERROR_DEBUG();
}

void GLESDebugDraw::DrawString(int x, int y, const char *string, ...)
{
//    NSLog(@"DrawString: unsupported: %s", string);
    //printf(string);
    /* Unsupported as yet. Could replace with bitmap font renderer at a later date */
}

void GLESDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    mShaderProgram->use();
    mShaderProgram->setUniformsForBuiltins();

    GLfloat                glVertices[] = {
        aabb->lowerBound.x * mRatio, aabb->lowerBound.y * mRatio,
        aabb->upperBound.x * mRatio, aabb->lowerBound.y * mRatio,
        aabb->upperBound.x * mRatio, aabb->upperBound.y * mRatio,
        aabb->lowerBound.x * mRatio, aabb->upperBound.y * mRatio
    };

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, glVertices);
//    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR, color.r, color.g, color.b, 1);
    mShaderProgram->setUniformLocationWith4f(mColorLocation, color.r, color.g, color.b, 1);

    glDrawArrays(GL_LINE_LOOP, 0, 4);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,4);

    CHECK_GL_ERROR_DEBUG();
}
