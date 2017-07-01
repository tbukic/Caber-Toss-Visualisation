#ifndef CABER_SCENE_H_INCLUDED
#define CABER_SCENE_H_INCLUDED

#include <SFML/Graphics.hpp>

class CaberShape : public sf::Transformable,
		public sf::Drawable,
		private sf::NonCopyable {
	
};

#endif // CABER_SCENE_H_INCLUDED
