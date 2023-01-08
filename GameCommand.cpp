#include "Model.h"
#include "GameCommand.h"
#include "Invalid_Input.h"
#include "View.h" 

using namespace std;

int main(){

    Model* m1 = new Model;
    View* v1 = new View;
    m1->ShowStatus();
    m1->Display(*v1);

    cout << "Enter the game command: " << endl;
    char code;
    int id1 = 0;
    int id2 = 0;
    int x = 0;
    int y = 0;
    cin >> code;
    if (cin.fail()){
        throw Invalid_Input("Was expecting a character.");
    }

    while (code != 'q') {

        try {

            if (code == 'm') {
                cin >> id1;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                cin >> id2;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                cin >> x;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                if (id2 < 0 || id2 > 20 || x < 0 || x > 20)
                    throw Invalid_Input("Location is out of bounds.");

                Point2D p1(id2, x);
                DoMoveCommand(*m1, id1, p1);
            }
            else if (code == 'c') {
                cin >> id1;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                cin >> id2;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                DoMoveToCenterCommand(*m1, id1, id2);
            }
            else if (code == 'g') {
                cin >> id1;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                cin >> id2;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                DoMoveToGymCommand(*m1, id1, id2);
            }
            else if (code == 's') {
                cin >> id1;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                DoStopCommand(*m1, id1);
            }
            else if (code == 'p') {
                cin >> id1;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                cin >> id2;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                DoRecoverInCenterCommand(*m1, id1, id2);
            }
            else if (code == 'b') {
                cin >> id1;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                cin >> id2;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                DoBattleCommand(*m1, id1, id2);
            }
            else if (code == 'a')
                DoAdvanceCommand(*m1, *v1);
            else if (code == 'r')
                DoRunCommand(*m1, *v1);


            //accounts for new command
            else if (code == 'n'){
                char code2;
                cin >> code2;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting a character.");
                }
                cin >> id1;
                if (cin.fail()){
                    throw Invalid_Input("Was expecting an integer.");
                }
                cin >> x;
                cin >> y;
                if (id2 < 0 || id2 > 20 || x < 0 || x > 20)
                    throw Invalid_Input("Location is out of bounds.");

                Point2D newLoc(x,y);
                m1->NewCommand(code2, id1,newLoc);
            }



            cout << "Enter the game command: " << endl;
            cin >> code;
            if (cin.fail()){
                throw Invalid_Input("Was expecting a character.");
            }

        } //try block

        catch (Invalid_Input& except){
            cout << "Invalid input: " << except.msg_ptr << endl;
            break;
        }

    }
    exit(EXIT_SUCCESS);
    return 0;
}

void DoMoveCommand(Model & model, int trainer_id, Point2D p1){
    Trainer* modelTrainer = model.GetTrainerPtr(trainer_id);
    if (modelTrainer != NULL){
        (*modelTrainer).StartMoving(p1);
        cout << "Moving " << modelTrainer->GetName() << " to " << p1 << endl;
    }
    else  
        cout << "Error: Please enter a valid command!" << endl;
}

void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id){
    Trainer* modelTrainer = model.GetTrainerPtr(trainer_id);
    PokemonCenter* modelCenter = model.GetPokemonCenterPtr(center_id);
    if (modelTrainer != NULL && modelCenter != NULL){
        (*modelTrainer).StartMovingToCenter(modelCenter);
        cout << "Moving " << modelTrainer->GetName() << " to PokemonCenter " << modelCenter->GetId() << endl;
    }
    else
        cout << "Error: Please enter a valid command!" << endl;
}

void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id){
    Trainer* modelTrainer = model.GetTrainerPtr(trainer_id);
    PokemonGym* modelGym = model.GetPokemonGymPtr(gym_id);
    if (modelTrainer != NULL && modelGym != NULL){
        (*modelTrainer).StartMovingToGym(modelGym);
        cout << "Moving " << modelTrainer->GetName() << " to PokemonGym " << modelGym->GetId() << endl;
    }
    else
        cout << "Error: Please enter a valid command!" << endl;
}

void DoStopCommand(Model & model, int trainer_id){
    Trainer* modelTrainer = model.GetTrainerPtr(trainer_id);
    if (modelTrainer != NULL){
        (*modelTrainer).Stop();
        cout << "Stopping " << modelTrainer->GetName() << endl;
    }
    else
        cout << "Error: Please enter a valid command!" << endl;
}

void DoBattleCommand(Model & model, int trainer_id, unsigned int battles){
    Trainer* modelTrainer = model.GetTrainerPtr(trainer_id);
    if (modelTrainer != NULL){
        (*modelTrainer).StartBattling(battles);
        cout << modelTrainer->GetName() << " is battling." << endl;
    }
    else
        cout << "Error: Please enter a valid command!" << endl;   
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed){
    Trainer* modelTrainer = model.GetTrainerPtr(trainer_id);
    //modelTrainer->current_center
    if (modelTrainer != NULL){
        //(*modelTrainer).
        (*modelTrainer).StartRecoveringHealth(potions_needed);
        cout << "Recovering " << modelTrainer->GetName() << "'s Pokemon's health." << endl;
    }
    else
        cout << "Error: Please enter a valid command!" << endl;
}

void DoAdvanceCommand(Model& model, View& view){
    cout << "Advancing one tick." << endl;
    model.Model::Update();
    model.Model::ShowStatus();
    model.Model::Display(view);
}

void DoRunCommand(Model& model, View& view){
    cout << "Advancing to next event." << endl;
    for (int i = 0; i < 5; i++){        //advances 5 ticks of itme
        if (model.Model::Update())      //or breaks if an event occurs
            break;
        model.Model::ShowStatus();
        model.Model::Display(view);
    }
}