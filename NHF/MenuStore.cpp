#include "MenuStore.hpp"

#include "GameStage.hpp"


MenuStore::MenuStore(AppData& appData) : Store{ appData } {
	_appData.assets.loadFont("Air Millhouse", "./Assets/airmill_o.ttf");

	//create tmp button

	// move it to _widgets

}
