#include "List.h"

void List::excuteList(string sdate) {
    sdate.erase(remove(sdate.begin(), sdate.end(), '-'), sdate.end());
    vector<vector<string>> fileData = File::getBooking(sdate);

    size_t row = fileData.size();
    size_t col = fileData[0].size();

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

