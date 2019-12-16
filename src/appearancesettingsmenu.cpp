#include <QFontDialog>
#include "appearancesettingsmenu.h"
#include "game.h"

AppearanceSettingsMenu::AppearanceSettingsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&appearanceSettingsLabel, 0, 1);
    appearanceSettingsLabel.setVisible(false);
    appearanceSettingsLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    appearanceSettingsLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    grid->addWidget(&inventoryTypeLabel, 1, 0);
    inventoryTypeLabel.setVisible(false);
    inventoryTypeLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&inventoryTypeSelector, 1, 1);
    inventoryTypeSelector.setCurrentIndex(-1);
    inventoryTypeSelector.setVisible(false);
    inventoryTypeSelector.setEnabled(false);

    grid->addWidget(&fontLabel, 2, 0);
    fontLabel.setVisible(false);
    fontLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&fontSetupButton, 2, 1);
    fontSetupButton.setVisible(false);
    fontSetupButton.setEnabled(false);
    connect(&fontSetupButton, SIGNAL(released()), this, SLOT(fontSetupFunction()));

    grid->addWidget(&colorThemeLabel, 3, 0);
    colorThemeLabel.setVisible(false);
    colorThemeLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&colorThemeSelector, 3, 1);
    colorThemeSelector.setCurrentIndex(-1);
    colorThemeSelector.setVisible(false);
    colorThemeSelector.setEnabled(false);

    grid->addWidget(&backgroundImagesLabel, 4, 0);
    backgroundImagesLabel.setWordWrap(true);
    backgroundImagesLabel.setVisible(false);
    backgroundImagesLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&backgroundImagesSwitch, 4, 1);
    backgroundImagesSwitch.setTristate(false);
    backgroundImagesSwitch.setVisible(false);
    backgroundImagesSwitch.setEnabled(false);

    grid->addWidget(&backButton, 5, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void AppearanceSettingsMenu::display() {
    this->pre_display();

    appearanceSettingsLabel.setText(game->str.appearanceSettings);
    appearanceSettingsLabel.setVisible(true);

    inventoryTypeLabel.setText(game->str.inventoryType);
    inventoryTypeLabel.setVisible(true);

    inventoryTypeSelector.addItem(game->str.popUp);
    inventoryTypeSelector.addItem(game->str.builtIn);
    inventoryTypeSelector.setCurrentIndex((int)game->inventoryType);
    inventoryTypeSelector.setVisible(true);
    inventoryTypeSelector.setEnabled(true);
    inventoryTypeUpdater = connect(&inventoryTypeSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
    [this](int index) {
        if (index != -1) {
            this->game->inventoryType = (InventoryType)index;
        }
    });

    fontLabel.setText(game->str.font);
    fontLabel.setVisible(true);

    fontSetupButton.setText(game->str.setup);
    fontSetupButton.setVisible(true);
    fontSetupButton.setEnabled(true);

    colorThemeLabel.setText(game->str.colorTheme);
    colorThemeLabel.setVisible(true);

    colorThemeSelector.addItem(game->str.lightTheme);
    colorThemeSelector.addItem(game->str.darkTheme);
    colorThemeSelector.setCurrentIndex((int)game->colorTheme);
    colorThemeSelector.setVisible(true);
    colorThemeSelector.setEnabled(true);
    colorThemeUpdater = connect(&colorThemeSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
    [this](int index) {
        if (index != -1) {
            this->game->colorTheme = (ColorTheme)index;
            this->game->cfg.applyColorTheme(this->game->colorTheme);
        }
    });

    backgroundImagesLabel.setText(game->str.showBackgroundImages);
    backgroundImagesLabel.setVisible(true);

    backgroundImagesSwitch.setVisible(true);
    backgroundImagesSwitch.setEnabled(true);
    backgroundImagesSwitch.setChecked(game->showBgImages);
    backgroundImagesUpdater = connect(&backgroundImagesSwitch, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged),
    [this](int state) {
        this->game->showBgImages = bool(state);
    });

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void AppearanceSettingsMenu::fontSetupFunction() {
    QFont newFont = QFontDialog::getFont(nullptr, game->textFont, nullptr);
    game->setFont(newFont);
    game->console.setFont(newFont);
    game->aboutMenu.setFont(newFont);
    game->gameMenu.getPopUpInventoryTable().setFont(newFont);
}

void AppearanceSettingsMenu::backFunction() {
    this->hide();
    game->settingsMenu.display();
}

void AppearanceSettingsMenu::hide() {
    this->pre_hide();

    appearanceSettingsLabel.setVisible(false);

    inventoryTypeLabel.setVisible(false);

    inventoryTypeSelector.setVisible(false);
    inventoryTypeSelector.setEnabled(false);
    disconnect(inventoryTypeUpdater);
    inventoryTypeSelector.clear();

    fontLabel.setVisible(false);

    fontSetupButton.setVisible(false);
    fontSetupButton.setEnabled(false);

    backgroundImagesLabel.setVisible(false);

    backgroundImagesSwitch.setVisible(false);
    backgroundImagesSwitch.setEnabled(false);
    disconnect(backgroundImagesUpdater);

    colorThemeLabel.setVisible(false);

    colorThemeSelector.setVisible(false);
    colorThemeSelector.setEnabled(false);
    disconnect(colorThemeUpdater);
    colorThemeSelector.clear();

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

AppearanceSettingsMenu::~AppearanceSettingsMenu() {

}
