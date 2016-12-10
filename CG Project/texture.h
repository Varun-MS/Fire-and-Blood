//
//  texture.hpp
//  CG Project
//
//  Created by Varun Murthy Suravarapu on 04/05/16.
//  Copyright © 2016 Varun Murthy Suravarapu. All rights reserved.
//

#ifndef texture_h
#define texture_h

#include <iostream>
#include <SDL2/SDL.h>

//Texture Wrapper Class
class Texture
{
    public:
        //Initializes variables
        Texture();
        
        //Deallocates memory
        ~Texture();
        
        //Loads image at specified path
        bool LoadFromFile( std::string path );
        
    //#ifdef _SDL_TTF_H
        //Creates image from font string
        bool LoadFromRenderedText( std::string textureText, SDL_Color textColor );
    //#endif
        
        //Deallocates texture
        void Free();
        
        //Set color modulation
        void SetColor( Uint8 red, Uint8 green, Uint8 blue );
        
        //Set blending
        void SetBlendMode( SDL_BlendMode blending );
        
        //Set alpha modulation
        void SetAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void Render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        
        //Gets image dimensions
        int GetWidth();
        int GetHeight();
        
    private:
        //The actual hardware texture
        SDL_Texture* mTexture;
        
        //Image dimensions
        int mWidth;
        int mHeight;
};

#endif /* texture_h */
