#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace sfm {
	template <class T>
	T dot( const sf::Vector2<T>& vec1, const sf::Vector2<T>& vec2 ) {
		return vec1.x * vec1.x + vec2.y * vec2.y;
	}

	template <class T>
	float length( const sf::Vector2<T>& vec ) {
		return std::sqrt( dot( vec, vec ) );
	}

	template <class T>
	void normalize( sf::Vector2f& vec ) {
		vec /= length( vec );
	}

	template <class T>
	sf::Vector2f getNormalized( const sf::Vector2<T>& vec ) {
		sf::Vector2f vec2 = static_cast< sf::Vector2f >(vec);
		normalize<T>( vec2 );
		return vec2;
	}
}

