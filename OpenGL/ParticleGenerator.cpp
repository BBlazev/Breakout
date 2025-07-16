#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount)
    : shader(shader), texture(texture), amount(amount)
{
    srand((unsigned)time(NULL));    
    this->init();
}

void ParticleGenerator::Update(float dt, GameObject& object)
{
    _spawnAcc += spawnRate * dt;
    unsigned int newParticles = (unsigned int)_spawnAcc;
    _spawnAcc -= newParticles;

    for (unsigned int i = 0; i < newParticles; ++i)
    {
        unsigned int idx = firstUnusedParticle();
        respawnParticle(this->particles[idx], object);
    }

    for (auto& p : particles)
    {
        if (p.Life > 0.0f)
        {
            p.Life -= dt;
            if (p.Life > 0.0f)
            {
                p.Position += p.Velocity * dt;
                p.Color.a -= dt * 2.5f;
            }
        }
    }
}

void ParticleGenerator::Draw()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    this->shader.Use();
    for (Particle particle : this->particles)
    {
        if (particle.Life > 0.0f)
        {
            this->shader.SetVector2f("offset", particle.Position);
            this->shader.SetVector4f("color", particle.Color);
            this->shader.SetInteger("sprite", 0);
            this->shader.SetFloat("pixelSize", 2.0f);
            this->shader.SetInteger("colorLevels", 2);
            this->shader.SetFloat("noiseIntensity", 0.15f);

            this->texture.Bind();
            glBindVertexArray(this->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init()
{
    unsigned int VBO;
    float particle_quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    for (unsigned int i = 0; i < this->amount; ++i)
        this->particles.push_back(Particle());
}
unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
    for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
        if (this->particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    for (unsigned int i = 0; i < lastUsedParticle; ++i) {
        if (this->particles[i].Life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle& p, const GameObject& object)
{
    glm::vec2 pos = object.Position;

    glm::vec2 dir = glm::normalize(object.Velocity);
    glm::vec2 perp(-dir.y, dir.x);
    float   jitterAmt = 5.0f; // pixels
    float   off = ((rand() % 100) / 100.0f - 0.5f) * 2.0f * jitterAmt;
    pos += perp * off;

    p.Position = pos;
    float c = 0.5f + ((rand() % 100) / 100.0f) * 0.5f;
    p.Color = glm::vec4(c, c, c, 1.0f);
    p.Life = 1.0f;

    p.Velocity = -dir * glm::length(object.Velocity) * 0.1f;
}
