#pragma once

#include "../component.h"


class KeysTypedBuffer
{
private:
	std::vector<sf::Event> key_type_events;

public:
	void process(sf::Event event)
	{
		if (event.type == sf::Event::TextEntered || event.type == sf::Event::KeyPressed)
		{
			key_type_events.push_back(event);
		}
	}

	void clear()
	{
		key_type_events.clear();
	}

	std::vector<sf::Event> getKeyTypeEvents() { return key_type_events; }
};

class TextField : public Component
{
protected:
	sf::Text text;
	sf::RectangleShape shape;

	sf::Color outline_color = sf::Color(230, 230, 230, 255);
	sf::Color inactive_fill_color = sf::Color(230, 230, 230, 255);
	sf::Color active_fill_color = sf::Color(230, 230, 230, 255);

	bool active = false;

	KeysTypedBuffer* keys_typed_buffer = 0;

	int cursor = -1;

	std::map<sf::Keyboard::Key, bool> control_keys;


protected:
	void set_control_keys()
	{
		control_keys.insert({ sf::Keyboard::Backspace, false });
		control_keys.insert({ sf::Keyboard::Delete, false });
		control_keys.insert({ sf::Keyboard::Enter, false });
		control_keys.insert({ sf::Keyboard::Up, false });
		control_keys.insert({ sf::Keyboard::Down, false });
		control_keys.insert({ sf::Keyboard::Left, false });
		control_keys.insert({ sf::Keyboard::Right, false });
	}

public:
	TextField(KeysTypedBuffer* s_keys_typed_buffer)
	{
		set_control_keys();

		setKeysTypedBuffer(s_keys_typed_buffer);

		text.setFillColor(sf::Color::Black);
		text.setString("");
	}

	TextField(KeysTypedBuffer* s_keys_typed_buffer, Position p) : Component(p)
	{
		set_control_keys();

		setKeysTypedBuffer(s_keys_typed_buffer);

		text.setFillColor(sf::Color::Black);
		text.setString("");
	}

	TextField(KeysTypedBuffer* s_keys_typed_buffer, sf::Text s_text)
	{
		set_control_keys();

		setKeysTypedBuffer(s_keys_typed_buffer);

		setText(s_text);
	}

	TextField(KeysTypedBuffer* s_keys_typed_buffer, sf::Text s_text, sf::Color s_outline_color, sf::Color s_inactive_fill_color, sf::Color s_active_fill_color)
	{
		set_control_keys();

		setKeysTypedBuffer(s_keys_typed_buffer);

		setText(s_text);
		setOutlineColor(s_outline_color);
		setInactiveFillColor(s_inactive_fill_color);
		setActiveFillColor(s_active_fill_color);
	}

	TextField(KeysTypedBuffer* s_keys_typed_buffer, sf::Color s_outline_color, sf::Color s_inactive_fill_color, sf::Color s_active_fill_color)
	{
		set_control_keys();

		setKeysTypedBuffer(s_keys_typed_buffer);

		text.setFillColor(sf::Color::Black);
		text.setString("");

		setOutlineColor(s_outline_color);
		setInactiveFillColor(s_inactive_fill_color);
		setActiveFillColor(s_active_fill_color);
	}

	void setText(sf::Text s_text)
	{
		text = s_text;
		text.setPosition(position.x, position.y);
		position.height = text.getCharacterSize();
		//sf::FloatRect rect = text.getLocalBounds();
		//position.width = rect.width;
		//position.height = rect.height;
	}

	sf::Text getText() { return text; }

	void setActiveFillColor(sf::Color s_fill_color)
	{
		active_fill_color = s_fill_color;
	}

	void setInactiveFillColor(sf::Color s_fill_color)
	{
		inactive_fill_color = s_fill_color;
	}

	void setOutlineColor(sf::Color s_outline_color)
	{
		outline_color = s_outline_color;
	}

	sf::Color getActiveFillColor() { return active_fill_color; }

	sf::Color getInactiveFillColor() { return inactive_fill_color; }

	sf::Color getOutlineColor() { return outline_color; }

	void setWidth(int width) { position.width = width; }

	bool isActive() { return active; }

	void activate()
	{
		active = true;
		std::string content = text.getString();
		cursor = content.length();
		content += "|";
		text.setString(content);
	}

	void deactivate()
	{
		active = false;
		std::string content = text.getString();
		if (cursor)
			content.erase(cursor, 1);
		cursor = -1;
		text.setString(content);
	}

	void setKeysTypedBuffer(KeysTypedBuffer* s_keys_typed_buffer)
	{
		keys_typed_buffer = s_keys_typed_buffer;
	}

	KeysTypedBuffer* getKeysTypedBuffer() { return keys_typed_buffer; }

	void render(sf::RenderWindow* window)
	{
		if (active)
			shape.setFillColor(active_fill_color);
		else
			shape.setFillColor(inactive_fill_color);
		shape.setOutlineThickness(2);
		shape.setOutlineColor(outline_color);
		shape.setPosition(position.x, position.y);
		shape.setSize(sf::Vector2f(position.width, position.height));
		text.setPosition(position.x, position.y);

		window->draw(shape);
		window->draw(text);

		// check if the text field is activated
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
			sf::Vector2f textfield_pos = sf::Vector2f(position.x, position.y);
			sf::Vector2f textfield_size = sf::Vector2f(position.width, position.height);
			if (
				mouse_pos.x <= textfield_pos.x + textfield_size.x &&
				mouse_pos.x >= textfield_pos.x &&
				mouse_pos.y <= textfield_pos.y + textfield_size.y &&
				mouse_pos.y >= textfield_pos.y
				)
			{
				if (!active)
				{
					activate();
				}
			}
			else
			{
				deactivate();
			}
		}

		if (active)
		{
			for (sf::Event key_type_event : keys_typed_buffer->getKeyTypeEvents())
			{
				std::string content = text.getString();

				if (key_type_event.key.code == sf::Keyboard::Backspace && cursor > 0)
				{
					std::string new_content = content.substr(0, cursor - 1);
					new_content += content.substr(cursor, content.length() - cursor - 1);
					cursor--;
					text.setString(new_content);
				}
				else if (key_type_event.key.code == sf::Keyboard::Backspace && cursor < content.length() - 1)
				{
					content.erase(cursor + 1, 1);
					cursor--;
					text.setString(content);
				}
				else if (key_type_event.type == sf::Event::TextEntered)
				{
					if (key_type_event.text.unicode < 128)
					{
						std::string content = text.getString();
						char c = static_cast<char>(key_type_event.text.unicode);
						content.insert(cursor, std::string(1, c));
						cursor++;
						text.setString(content);
					}
				}
			}
			keys_typed_buffer->clear();

			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && control_keys.at(sf::Keyboard::Backspace) == true)
			{
				auto it = control_keys.find(sf::Keyboard::Backspace);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
			{
				auto it = control_keys.find(sf::Keyboard::Delete);
			}
		}
	}
};