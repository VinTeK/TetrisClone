/**
Templatized resource manager that loads a type of resource and holds all the
pointers to them.

Code borrowed from https://github.com/TylerSandman/marvin/blob/master/Include/ResourceManager.h
*/


#pragma once


#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <SFML/Graphics.hpp>


template <typename Res>
class ResourceManager {
public:
	/**
	Creates a new resource object located at the given path with the given name.
	The dynamic allocation is neatly handled with smart pointers.
	*/
	void load(const std::string& path, const std::string& name);
	/**
	Returns a reference to the resource with the given name.
	*/
	Res& get(const std::string& name) const;

private:
	std::map <std::string, std::unique_ptr<Res> > m_resources;
};


/* Typedefs for convenience. */
typedef ResourceManager<sf::Texture> TextureManager;
typedef ResourceManager<sf::Font> FontManager;


template <typename Res>
void ResourceManager<Res>::load(const std::string& path, const std::string& name)
{
	/* Dynamic allocation needed here, but thank god for smart pointers! */
	std::unique_ptr<Res> res(new Res());

	if (!res->loadFromFile(path))
		throw std::runtime_error("failed to load resource: " + path);

	/* Make sure there is only one instance of a resource loaded.*/
	if (m_resources.find(name) != m_resources.end())
		throw std::runtime_error("already loaded resource: " + name);

	/* Move semantics for the smart pointer; the pointer is not copied, only
	ownership is transferred. */
	m_resources[name] = std::move(res);
}


template <typename Res>
Res& ResourceManager<Res>::get(const std::string& name) const
{
	auto itr = m_resources.find(name);

	if (itr == m_resources.end())
		throw std::runtime_error("could not retrieve resource: " + name);

	return *(itr->second);
}
