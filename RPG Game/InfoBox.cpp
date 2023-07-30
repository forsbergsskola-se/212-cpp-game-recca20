#include "InfoBox.h"

InfoBox::InfoBox()
{
	//load font with font size 16
	font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 16);
}

InfoBox::~InfoBox()
{
	if (textTexture != NULL)
		SDL_DestroyTexture(textTexture);
	
	TTF_CloseFont(font);
}

void InfoBox::setup(SDL_Renderer* renderer)
{    
	this->renderer = renderer;
}

void InfoBox::setText(string text)
{
	//only bother changing text if its different from before and not an empty string
	if (this->text != text && text != "")
	{
		//destroy old text texture before creating a new one
		if (textTexture != NULL)
			SDL_DestroyTexture(textTexture);

		this->text = text;

		//build text texture using font and text string
		SDL_Color textColor = { 0,0,0,0 };//RGBA(0000 is black)(255,255,255,0 is white)
		//Create surface out of our text
		SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
		//convert surface into texture
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		//delete surface properly
		SDL_FreeSurface(textSurface);

		//work out width and height of geneerated texture
		SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
		//work out how to centre this text in the screen
		textRect.x = 320 / 2 - textRect.w / 2;//half screen - half width
		textRect.y = 240 / 2 - textRect.h / 2;//half screen - half height

		//work out our box rectangle with some padding
		boxRect.x = textRect.x - 4;
		boxRect.y = textRect.y - 4;
		boxRect.w = textRect.w + 8;
		boxRect.h = textRect.h + 8;
	}
}

void InfoBox::draw()
{
	if (visible && textTexture != NULL && text != "")
	{
		//draw box
		SDL_SetRenderDrawColor(renderer, 217, 43, 90, 255);
		SDL_RenderFillRect(renderer, &boxRect);

		//draw border
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &boxRect);

		//draw text to screen
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	}
}
