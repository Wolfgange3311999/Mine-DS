//
// Created by matthew on 10/29/18.
//

#include "GraphicsSystem.hpp"
#include <nds.h>
#include "Texture.hpp"

// Data files generated by grit:
#include <block_small.h>
#include <mobs.h>
#include <sub_bg.h>


Texture::TextureImage::TextureImage(unsigned long tilesBytes, unsigned long palBytes) :
        tiles(tilesBytes / 4), pal(palBytes / 2) {}

void Texture::TextureImage::read(FILE *file, const unsigned int *defaultTiles, const uint16_t *defaultPal) {
    if (!file || fread(tiles.data(), sizeof(uint32_t), tiles.size(), file) != tiles.size() ||
        fread(pal.data(), sizeof(uint16_t), pal.size(), file) != pal.size()) {
        tiles.assign(defaultTiles, defaultTiles + tiles.size());
        pal.assign(defaultPal, defaultPal + pal.size());
    }
}

void Texture::load(FILE *file) {
    block.read(file, block_smallTiles, block_smallPal);
    mob.read(file, mobsTiles, mobsPal);
    subBg.read(file, sub_bgTiles, sub_bgPal);
}

void Texture::loadDefault() {
    load(nullptr);
}

Texture::Texture() :
        block(block_smallTilesLen, block_smallPalLen),
        mob(mobsTilesLen, mobsPalLen),
        subBg(sub_bgTilesLen, sub_bgPalLen) {}