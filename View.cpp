#include "View.h"
#include "Point2D.h"

using namespace std;

bool View::GetSubscripts(int &out_x, int &out_y, Point2D location){
    Vector2D locToOrg = location - origin;
    out_x = int(locToOrg.x / scale);
    out_y = int(locToOrg.y / scale);
    if ( (out_x <= size) && (out_y <= size) ){
        return true;
    }
    else {
        cout << "An object is outside the display." << endl;
        return false;
    }
}

View::View(){
    size = 11;
    scale = 2;
} 

void View::Clear(){
    for (int j = size-1; j >= -1; j--) {
        for (int i = -1; i <= size-1; i++) {
            //resets dot marks in grid
            if (i >= 0 && j >=0) {
                    grid[i][j][0] = '.';
                    grid[i][j][1] = ' ';
            }
        }
    }
}

void View::Plot(GameObject* ptr){
    int out_x, out_y;
    bool subscriptsValid = GetSubscripts(out_x, out_y, ptr->GetLocation());
    if (subscriptsValid){
        if (grid[out_x][out_y][0] != '.') {     //if an object already occupies this space
            grid[out_x][out_y][0] = '*';
            grid[out_x][out_y][1] = ' ';
        }
        else if (!ptr->ShouldBeVisible()){
            grid[out_x][out_y][0] = '.';
            grid[out_x][out_y][1] = ' ';
        }
        else  
            (*ptr).DrawSelf(grid[out_x][out_y]);       
    }
}


void View::Draw() {
    for (int j = size-1; j >= -1; j--) {
        for (int i = -1; i <= size-1; i++) {
            //grid axis
            if (i == -1 && j%2 == 0) {
                cout << j*2;
                if (j/5 == 0) {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 != 0) {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0) {
                cout << i*2;
                if (i/5 == 0) {
                    cout << " ";
                }
                cout << "  ";
            }
            //draw objects
            if (i >= 0 && j >=0) {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}