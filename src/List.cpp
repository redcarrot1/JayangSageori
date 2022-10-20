#include "List.h"

List::List(string sdate, string id) {
    this->sdate = sdate;
    this->id = id;
    sdate.erase(remove(sdate.begin(), sdate.end(), '-'), sdate.end());
    this->sdate = sdate;
    this->fileData = File::getBooking(this->sdate);

    /* Test Code
    cout << sdate << endl;
    cout << this->sdate;
    */
}

void List::excuteList() {
    int row = fileData.size();
    int col = fileData[0].size();

    /* Test Code
    cout << row << endl;
    cout << col << endl;
    */

    // 출력문은 테스트 후 수정하겠습니다. TODO
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << fileData[i][col] << "\t";
        }
        cout << endl;
    }
}

