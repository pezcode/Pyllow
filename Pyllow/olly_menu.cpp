#include "olly_menu.h"

#include <algorithm>

const t_menu OllyMenu::empty   = { NULL, NULL, K_NONE, NULL, NULL, 0 };
const t_menu OllyMenu::divider = { L"|", NULL, K_NONE, NULL, NULL, 0 };

const t_menu OllyMenu::fwd_standard   = { L">STANDARD", NULL, K_NONE, NULL, NULL, 0 };
const t_menu OllyMenu::fwd_fullcopy   = { L">FULLCOPY", NULL, K_NONE, NULL, NULL, 0 };
const t_menu OllyMenu::fwd_appearance = { L">APPEARANCE", NULL, K_NONE, NULL, NULL, 0 };

OllyMenu::OllyMenu()
{

}

OllyMenu::OllyMenu(const t_menu* menu, size_t count)
{
	add(menu, count);
}

OllyMenu::OllyMenu(const t_menu* menu)
{
	add(menu);
}

OllyMenu::OllyMenu(const OllyMenu& menu)
{
	add(menu);
}

OllyMenu::~OllyMenu()
{
	free(items.data(), items.size());
}

OllyMenu& OllyMenu::operator=(OllyMenu menu)
{
	std::swap(items, menu.items);
	return *this;
}

void OllyMenu::clear()
{
	free(items.data(), items.size());
	items.clear();
}

std::vector<t_menu> OllyMenu::build() const
{
	std::vector<t_menu> menu = items;
	menu.push_back(empty);
	return menu;
}

void OllyMenu::add(const std::wstring& text, const std::wstring& help, int shortcut, MENUFUNC* callback, int index)
{
	t_menu item =
	{
		const_cast<wchar_t*>(text.c_str()),
		const_cast<wchar_t*>(help.c_str()),
		shortcut,
		callback,
		NULL,
		index
	};

	add(item);
}

void OllyMenu::add(const std::wstring& text, const std::wstring& help, int shortcut, const OllyMenu& menu)
{
	std::vector<t_menu> sub = menu.build();

	t_menu item =
	{
		const_cast<wchar_t*>(text.c_str()),
		const_cast<wchar_t*>(help.c_str()),
		shortcut,
		NULL,
		sub.data(),
		0
	};

	add(item);
}

void OllyMenu::add(const OllyMenu& menu)
{
	if(!menu.items.empty())
	{
		add(menu.items.data(), menu.items.size());
	}
}

bool OllyMenu::is_empty(const t_menu& item)
{
	return 0 == memcmp(&item, &empty, sizeof(t_menu));
}

size_t OllyMenu::menu_len(const t_menu* menu)
{
	size_t count = 0;

	while(!is_empty(*menu))
	{
		count++;
		menu++;
	}

	return count;
}

void OllyMenu::add(const t_menu& item)
{
	items.push_back(dup(item));
}

void OllyMenu::add(const t_menu* menu, size_t count)
{
	for(size_t i = 0; i < count; i++)
	{
		add(menu[i]);
	}
}

void OllyMenu::add(const t_menu* menu)
{
	add(menu, menu_len(menu));
}

void OllyMenu::free(const t_menu& item)
{
	delete[] item.name;
	delete[] item.help;
	if(item.submenu)
	{
		free(item.submenu);
		delete[] item.submenu;
	}
}

void OllyMenu::free(const t_menu* menu, size_t count)
{
	for(size_t i = 0; i < count; i++)
	{
		free(menu[i]);
	}
}

void OllyMenu::free(const t_menu* menu)
{
	free(menu, menu_len(menu));
}

t_menu OllyMenu::dup(const t_menu& item)
{
	t_menu new_item = item;

	if(item.name)
	{
		new_item.name = new wchar_t[wcslen(item.name) + 1];
		wcscpy(new_item.name, item.name);
	}

	if(item.help)
	{
		new_item.help = new wchar_t[wcslen(item.help) + 1];
		wcscpy(new_item.help, item.help);
	}

	if(item.submenu)
	{
		new_item.submenu = dup(item.submenu);
	}

	return new_item;
}

t_menu* OllyMenu::dup(const t_menu* menu, size_t count)
{
	t_menu* new_menu = new t_menu[count + 1];

	for(size_t i = 0; i < count; i++)
	{
		new_menu[i] = dup(menu[i]);
	}

	new_menu[count] = empty;

	return new_menu;
}

t_menu* OllyMenu::dup(const t_menu* menu)
{
	return dup(menu, menu_len(menu));
}
