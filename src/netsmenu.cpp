#include <QRegExp>
#include "netsmenu.h"
#include "game.h"

static const int netsTimerInterval = 5 * 60 * 1000;

NetsMenu::NetsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&netsDescription, 0, 0, 1, SLOTS_COUNT);
    netsDescription.setVisible(false);

    for (int i = 0; i < SLOTS_COUNT; ++i) {
        grid->addWidget(&netSlotLabel[i], 1 + (i / 3) * 2, i % 3);
        netSlotLabel[i].setVisible(false);
        netSlotLabel[i].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        grid->addWidget(&netSlot[i], 2 + (i / 3) * 2, i % 3);
        netSlot[i].setVisible(false);
        netSlot[i].setEnabled(false);
    }

    grid->addWidget(&backButton, 3 + SLOTS_COUNT / 3 * 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));

    netsTimer.start(netsTimerInterval);
    connect(&netsTimer, SIGNAL(timeout()), this, SLOT(netsTimerTick()));
}

void NetsMenu::updateNets() {
    const QMap<QString, int> &inv = game->users[game->activeUser].inventory.get();
    auto it = inv.begin();
    for (int i = 0; i < SLOTS_COUNT; ++i) {
        netSlotLabel[i].setText(game->str.netSlot.arg(
            QString::number(i),
            nets[i] == "" ? game->str.empty : nets[i]
        ));

        netSlot[i].clear();
        netSlot[i].addItem("");
        netSlot[i].addItem(game->str.empty);
    }
    while (it != inv.end()) {
        if (QRegExp("net.*").exactMatch(it.key())) {
            for (int i = 0; i < SLOTS_COUNT; ++i) {
                netSlot[i].addItem(it.key() + " (" + QString::number(it.value()) + ')');
            }
        }
        ++it;
    }
}

void NetsMenu::foldNets() {
    for (int i = 0; i < SLOTS_COUNT; ++i) {
        if (nets[i] != "") {
            this->game->users[this->game->activeUser].inventory.changeItem(nets[i], 1);
            nets[i] = "";
        }
    }
}

void NetsMenu::netsTimerTick() {
    for (int i = 0; i < SLOTS_COUNT; ++i) {
        if (nets[i] != "") {
            if (nets[i] == "net.basic") {
                const int MOD = 100;
                std::uniform_int_distribution<> dist(1, 99);
                int rnd = dist(game->randomGenerator) % MOD;
                qDebug() << "loc:" << game->activeLocation;
                game->users[game->activeUser].inventory.
                        changeItem(game->locations[game->activeLocation].getFish(
                        qMin(rnd / (MOD / game->locations[game->activeLocation].getFishCount()),
                        game->locations[game->activeLocation].getFishCount() - 1)), 1);
                game->gameMenu.updateInventoryTable();
            }
        }
    }
}

bool NetsMenu::isDisplayed() const {
    return displayed;
}

void NetsMenu::display() {
    updateNets();

    netsDescription.setText(game->str.netsDescription);
    netsDescription.setVisible(true);

    #define X(i) \
    connect(&netSlot[i], static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), \
        [this](int index) { \
            if (index < 1) \
                return; \
            qDebug() << "before:" << nets[i]; \
            if (nets[i] != "") { \
                this->game->users[this->game->activeUser].inventory.changeItem(nets[i], 1); \
            } \
            if (index == 1) { \
                nets[i] = ""; \
            } else { \
                nets[i] = netSlot[i].itemText(index).split(' ').first(); \
                qDebug() << "after:" << netSlot[i].itemText(index).split(' ').first(); \
                this->game->users[this->game->activeUser].inventory.changeItem(nets[i], -1); \
            } \
            netSlot[i].setCurrentIndex(0); \
            updateNets(); \
            game->gameMenu.updateInventoryTable(); \
        });
    X(0); X(1); X(2);
    X(3); X(4); X(5);
    X(6); X(7); X(8);
    #undef X

    for (int i = 0; i < SLOTS_COUNT; ++i) {
        netSlotLabel[i].setVisible(true);

        netSlot[i].setVisible(true);
        netSlot[i].setEnabled(true);
    }

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void NetsMenu::backFunction() {
    this->hide();
    game->gameMenu.display();
}

void NetsMenu::hide() {
    netsDescription.setVisible(false);

    for (int i = 0; i < SLOTS_COUNT; ++i) {
        netSlotLabel[i].setVisible(false);

        netSlot[i].setVisible(false);
        netSlot[i].setEnabled(false);
        netSlot[i].disconnect();
    }

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

NetsMenu::~NetsMenu() {
    netsTimer.stop();
}
