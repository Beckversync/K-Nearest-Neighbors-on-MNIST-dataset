#include "main.hpp"


template<typename T>
class List {
public:
   
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
   
};

 

template<typename T>
class successor : public List<T>
{
private:
    class Node{
    public:
        T pointer;
        Node* next;
    public:
        Node(T pointer, Node* next = nullptr) : pointer(pointer), next(next) {}
    };
private:
    Node* head;
    Node* tail;
    int size;
public:
    successor(){
        head = tail = nullptr;
        size = 0;

    }
    successor(const List<int>* listData) {
      
        for (int i = 0; i < listData->length(); ++i) {
            this->push_back(listData->get(i));
        }
    }
    ~successor(){
        this->clear();
        
    }
 
    void push_back(T value){
       
         Node* newNode = new Node(value);

        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        size=size+1;

    }

    void push_front(T value){
       
        Node* newNode = new Node(value);

        if (!head) {
            // Nễu list rỗng
            head = tail = newNode;
        }
        else {
            // Nếu list không rỗng
            newNode->next = head;
            head = newNode;
        }

        size=size+1;
    }
    void insert(int index, T value){
      
         if(index < 0 || index > size) return;

       
          Node* newNode = new Node(value);

        if (index == size) {
            // Insert at the end
            if (!head) {
                // If the list is empty, update both head and tail
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        else {
            // Insert at the specified index
            if (index == 0) {
                // Insert at the beginning
                newNode->next = head;
                head = newNode;
            }
            else {
                // Insert in the middle
                Node* current = head;
                for (int i = 0; i < index - 1; ++i) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        }

        size=size+1;
    }
    void remove(int index){
       
         if(index < 0 || index >= size) return;
          
        
        Node* temp;
    if (index == 0) {
        // Remove from the beginning
        temp = head;
        head = head->next;
    
        if (size==1) {
            // If the list becomes empty, update the tail as well
            temp=head;
            head = tail = nullptr;
        }
    }
    else {
        // Remove from the middle or end
        Node* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        temp = current->next;
        current->next = temp->next;

        if (index == size - 1) {
            // If removing the last element, update the tail
            tail = current;
        }
    }
    delete temp;
    size --;
    }

    T& get(int index) const{
       
        if(index < 0 || index >= this->length())  throw std::out_of_range("get(): Out of range");

   Node* temp = head;
        for (int i = 0; i < index; i++) {
          //  if(temp==0) cout<<"con tro null"<<endl;
            temp = temp->next;
        }
          //  if(temp==0) cout<<"con tro null"<<endl;

      return  temp->pointer;
    }
    int length() const{
        return size;
    }
    void clear(){
    
         Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }
    void print() const{
           if (size == 0) {
        
            return;

        }

        Node* temp = head;
        while (temp) {
            cout << (temp->pointer);
            if (temp->next) {
                cout << " ";
            }
            temp = temp->next;
        }

        
    }
    void reverse(){  
       
         if(this->size <= 1) return;
    //! curr là con trỏ hiện tại, pre là con trỏ phía trước
    Node* curr = this->head;
    Node* pre = this->head->next;
    for(int i = 0; i < this->size - 1; i++){
        //! lưu lại node i + 2
        Node* temp = pre->next;
        //! trỏ node i + 1 tới node i
        pre->next = curr;
        //! gán curr thành node i + 1 và pre thành node i + 2 (tăng lên)
        curr = pre;
        pre = temp;
    }
    
    //! cập nhật lại node đầu thành node cuối
    this->head->next = nullptr;
    this->tail = this->head;
    //! cập nhật node cuối thành node đầu
    this->head = curr; //! node cuối đang là curr
    }
    
};

class Dataset
{
private:
    List<List<int> *> *data;
    List<string> *nameCol;
    // You may need to define more
public:
    
    Dataset()
    {
        this->nameCol = new successor<string>();
        this->data = new successor<List<int> *>();
    }
   
    ~Dataset()
    {
        for (int i=0;i<data->length();i++){
        data->get(i)->clear();

    }
   //! xóa cập phát động các row trong data (pointer của Node trong data)
    for(int i = 0; i< data->length(); i++){
        delete this->data->get(i);
    }
    //! xóa data -> gọi tới hàm hủy xóa các cấp phát động Node trong data
    delete data;
    delete nameCol;
    }
    Dataset(const Dataset &other)
    {
        
    this->nameCol = new successor<string>();
    this->data = new successor<List<int>*>();

 for (int i = 0; i < other.nameCol->length(); ++i) {
        this->nameCol->push_back(other.nameCol->get(i));
    }
    // Sao chép nameCol từ other nameCol
     if (other.data->length() == 0) {
        // Cấp phát nameCol mới và trả về
        this->nameCol = new successor<string>();
        return;
    }
   

    // Nếu other có dữ liệu không rỗng, sao chép dữ liệu từ other
    if (other.data->length() > 0) {
        // Lặp qua từng cột của other.data và tạo bản sao cho đối tượng hiện tại
        for (int i = 0; i < other.data->length(); ++i) {
            List<int>* columnData = other.data->get(i);

           
            successor<int>* newColumnData = new successor<int>();

            // Lặp qua từng phần tử trong cột và đẩy nó vào cột mới
            for (int j = 0; j < columnData->length(); ++j) {
                newColumnData->push_back(columnData->get(j));
            }

            // Đẩy cột mới vào data trong dataset hiện tại
            this->data->push_back(newColumnData);
        }
    }
    else {
        // Nếu other rỗng, gán nameCol bằng nameCol trước đó
        
        this->nameCol = other.nameCol;
        this->data = nullptr; // Đặt data là nullptr hoặc xử lý tương tự như nameCol tùy vào yêu cầu của bạn.
    }
    }
    Dataset &operator=(const Dataset &other)
    {
        
      
            if (this != &other) {  // Kiểm tra gán cho chính nó
                // Xóa dữ liệu hiện tại
                delete this->nameCol;
                delete this->data;

                // Tạo các instance mới cho name column và data
                this->nameCol = new successor<string>();
                this->data = new successor<List<int>*>();
                for (int i = 0; i < other.nameCol->length(); ++i) {
                    this->nameCol->push_back(other.nameCol->get(i));
            
                }

        if (other.data->length() == 0) {
                    // Cấp phát nameCol mới và trả về
                    this->nameCol = new successor<string>();
                    this->data = new successor<List<int>*>();
                    return *this;
                }
       
      
        // Nếu other có data không rỗng, sao chép dữ liệu từ other
        if (other.data->length() > 0) {
            // Lặp qua từng cột trong other dataset
            for (int i = 0; i < other.data->length(); ++i) {
                // Lấy List<int>* từ other dataset
                List<int>* columnData = other.data->get(i);

              
                successor<int>* newColumnData = new successor<int>();

                // Lặp qua từng phần tử trong cột và đẩy nó vào cột mới
                for (int j = 0; j < columnData->length(); ++j) {
                    newColumnData->push_back(columnData->get(j));
                }

                // Đẩy cột mới vào data trong dataset hiện tại
                this->data->push_back(newColumnData);
            }
             
        }
    

    }
    return *this;
    }
     bool loadFromCSV(const char* fileName)
    {   
        ifstream file(fileName);
//* kiểm tra mở file
if (file.is_open()) {
    string str;
    int n;
    int count = 0;
    bool isTitle = true; // Biến để kiểm tra xem hàng này có phải là hàng title không

    // Đọc hàng title
    getline(file, str);
    istringstream ss(str);
    while (getline(ss, str, ',')) {
        nameCol->push_back(str);
    }

    // Kiểm tra cột cuối cùng của hàng title
    string lastValue;
    stringstream lastColumnCheck(str);
    while (getline(lastColumnCheck, lastValue, ',')) {}
    if (lastValue.empty()) {
        nameCol->push_back(" "); // Thêm một cột trống vào cột cuối cùng
    }

    while (file >> str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ',') str[i] = ' ';
        }
        stringstream ss(str);  
        List<int>* temp = new successor<int>();
        while (ss >> n) temp->push_back(n);

        data->push_back(temp);
    }
    return true;
}
    return false;
    }
    
 void getShape(int& nRows, int& nCols) const
{
    
    if (data->length() > 0 && data-> get(0)-> length() > 0) {
        nRows = this->data->length();
        nCols = this->data->get(0)->length();
    } else {
        nRows = 0;
        nCols = 0;
      //  if (nRows==0 && nCols==0)
       //     {
          //         throw std::out_of_range("get(): Out of range");
          //  }
       
    }
}
    void columns() const
    {
      
        nameCol->print();
         if (nameCol->length() == 0) {
            nameCol -> print();
    }
    }
    void printHead(int nRows = 5, int nCols = 5) const
{
   if (nRows <= 0 || nCols <= 0|| data->length() == 0 || data->get(0)->length() == 0) {
        return;
    }
    nRows = std::min(nRows, data->length());
    nCols = std::min(nCols,this->data->get(0)->length());
   
    if (nCols > 0) {
    //    OUTPUT << nameCol->get(0); 

        for (int i = 0; i < nCols-1; ++i) {
           
            cout << nameCol->get(i)<<" ";
          //  cout<<"in name\n";
        }
        cout << nameCol->get(nCols-1);
        if (nRows>0){
        cout << std::endl;
        }
    }

    for (int i = 0; i < nRows; ++i) {
    //    cout<<"bd\n";
        List<int>* rowData = data->get(i);
        if (i > 0) {
            cout << std::endl;
        }

        // Print values from data   
        for (int j = 0; j < nCols; ++j) {
            cout << rowData->get(j);
          //   cout<<"i: "<<i<<" j: "<<j<<"\n";
          //   cout<<rowData;
            if (j < nCols - 1) {
                cout << " ";
            }
        }
    }
    

}
  
    void printTail(int nRows = 5, int nCols = 5) const {
      if (nRows <= 0 || nCols <= 0) {
        return;
    }
    int startRow = std::max(0, data->length() - nRows);

    if (nRows > 0) {
        int startColName = std::max(0, nameCol->length() - nCols);
        bool isFirstValueName = true; 
        for (int i = startColName; i < nameCol->length(); ++i) {
            if (!isFirstValueName) {
                cout << " "; 
            } else {
                isFirstValueName = false;
            }
            cout << nameCol->get(i);
        }
       if(data ->length() >0)
       {
        cout <<std::endl;
       }
        
    }

    for (int i = startRow; i < data->length(); ++i) {
        List<int>* rowData = data->get(i);

        if (i > startRow) {
            cout << std::endl;
        }
        int startCol = std::max(0, rowData->length() - nCols);
        int endCol = std::min(rowData->length(), startCol + nCols);

        for (int j = startCol; j < endCol; ++j) {
            cout << rowData->get(j);
            if (j < endCol - 1) {
                cout << " ";
            }
        }
    }


}
    bool drop(int axis = 0, int index = 0, std::string columnName = "") {
    // Kiểm tra xem axis có hợp lệ không (0 hoặc 1)
    if (axis != 0 && axis != 1) {
        return false;
    }

    // Xóa hàng
    if (axis == 0) {
        // Kiểm tra xem index có hợp lệ không
        if (index < 0 || index >= data->length()) {
            return false;
        }

        // Xóa hàng tại vị trí index
        data->remove(index);
        
        return true;
    }

    // Xóa cột
    if (axis == 1) {
        // Kiểm tra xem danh sách tên cột có trống không
        if (nameCol->length() == 0) {
            return false;
        }

        // Tìm chỉ số của cột có tên columnName
        int columnIndex = -1;
        for (int i = 0; i < nameCol->length(); ++i) {
            if (nameCol->get(i) == columnName) {
                columnIndex = i;
                break;
            }
        }
        if (nameCol->length() == 1 && columnName == nameCol->get(0)) {
            nameCol->remove(0);
            for (int i = 0; i < data->length(); ++i) {
                data->get(i)->remove(0);
            }
            data -> clear();
            return true;
        }
        // Nếu không tìm thấy cột, trả về false
        if (columnIndex == -1) {
            return false;
        }

        // Xóa cột tương ứng từ nameCol
        nameCol->remove(columnIndex);

        // Xóa cột tương ứng từ mỗi hàng trong data
        for (int i = 0; i < data->length(); ++i) {
            data->get(i)->remove(columnIndex);
        }
    // cout<<"so luong hang va cot hien tai"<< nameCol->length() << "\n";
        return true;
    }

    return false; // Trường hợp còn lại, trả về false
}

Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const
{
  //if (  startRow > endRow || startCol > endCol ) throw std::out_of_range("get(): Out of range");
    if(this->data->length() ==0) return *this;
    if (startRow < 0 || startCol < 0 )
    {
      
        return Dataset();
    }

    startRow = std::max(0, startRow);
    startCol = std::max(0, startCol);

   
    if (endRow == -1)
    {
        endRow = data->length() - 1;
        
    }
    else
    {
    
        endRow = std::min(endRow, data->length() - 1);
    }

    if (endCol == -1)
    {
        endCol = nameCol->length() - 1;
    }
    else
    {
        
        endCol = std::min(endCol, nameCol->length() - 1);
    }

if ( startRow > endRow || startCol > endCol)
      {
        throw std::out_of_range("get(): Out of range");
      }
    Dataset extractedData;

   
    extractedData.nameCol = new successor<string>();
    extractedData.data = new successor<List<int> *>();



    int temp=1; 
    if (endCol == -1){
       temp= this ->nameCol -> length() -1;
    }
    else {
        temp = endCol;
    }
   
    for (int i = startCol; i <= temp; ++i) // ktra số cột
    { 
        extractedData.nameCol->push_back(nameCol->get(i));
    }
    for (int i = startRow; i <= endRow; ++i)
    {
        List<int> *newRow = new successor<int>();

        for (int j = startCol; j <= temp; ++j) 
        {
            if (i < data->length() && j < data->get(i)->length())
            {
             
                int cellValue = data->get(i)->get(j);

                newRow->push_back(cellValue);
              
            }
            else
            {
                
                newRow->push_back(0); 
            }
            
        }
          
    extractedData.data->push_back(newRow);
    }
    return extractedData;
}



    double distanceEuclidean(const List<int>* x, const List<int>* y) const{
       
         if (!x || !y) {
        return -1.0;  
    }


    if (x->length() != y->length()) {
        
        return -1.0; 
    }

   
    double sumSquaredDifferences = 0.0;
    for (int i = 0; i < x->length(); ++i) {
        int difference = x->get(i) - y->get(i);
        sumSquaredDifferences += difference * difference;
    }

   
    double euclideanDistance = std::sqrt(sumSquaredDifferences);

   return euclideanDistance;
    }

struct LabelDistance {
    int label;
    double distance;

    
    LabelDistance(int label, double distance) : label(label), distance(distance) {}
};


bool compareByDistance(const LabelDistance &a, const LabelDistance &b) {
    return a.distance < b.distance;
}
void bubbleSort(double* distance, int* label, int length)const {
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (distance[j] > distance[j + 1]) {
                // Hoán đổi khoảng cách
                double tempDist = distance[j];
                distance[j] = distance[j + 1];
                distance[j + 1] = tempDist;
                
                // Hoán đổi nhãn tương ứng
                int tempLabel = label[j];
                label[j] = label[j + 1];
                label[j + 1] = tempLabel;
            }
        }
    }
}
Dataset predict(const Dataset& X_train, const Dataset& Y_train,int k) const
    {

        Dataset result;

        result.nameCol = new successor<string>();
        result.nameCol->push_back("label");
        result.data = new successor<List<int> *>();
        if (k <= 0 || this->getData()->length() == 0 || X_train.getData()->length() == 0)
            return result;
        if (k > Y_train.getData()->length())
        {
            k = Y_train.getData()->length();
        }


        int numRows = this->getData()->length();
        int numCols = this->nameCol->length();
        if (numCols == 0) {
            return result;
        }

        for (int i = 0; i < 1; ++i) {
            result.nameCol->push_back(Y_train.nameCol->get(i));
        }

        int length_train = X_train.getData()->length();
        //  cout<<length_train<<"\n";

      if (k>=length_train) {
        throw std::out_of_range("get(): Out of range");
     }

       // int x, y; X_train.getShape(x, y); cout << x << "/" << y << endl;
        //int m,n; Y_train.getShape(m, n); cout << m << "/" << n << endl;

        int label[500]{};// = new int[numRows] {}; // Mảng lưu nhãn
        double distance[500]{};// = new double[length_train] {}; // Mảng lưu khoảng cách

        //  cout<<numRows<<"\n";
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < length_train; j++) {//số hàng của X_train
                // Tính khoảng cách giữa hàng i của X_test và hàng j của X_train
                double dist = distanceEuclidean(this->getData()->get(i), X_train.getData()->get(j));
                distance[j] = dist;
                label[j] = Y_train.getData()->get(j)->get(0); // Cập nhật nhãn    
               
            }
            
            bubbleSort(distance, label, length_train);
            
            int countArray[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            
            for (int m = 0; m < k; m++)
            {
                countArray[(label[m])] += 1;
            }
            int maxCount = countArray[0];
            int maxLabel = 0;
            for (int n = 1; n < 10; ++n) {
                if (countArray[n] > maxCount) {
                    maxCount = countArray[n]; maxLabel = n;
                }
            }
            for (int j = 1; j < 10; ++j) {
                if (countArray[j] > maxCount) {
                    maxCount = countArray[j];
                    maxLabel = j;
                }
            }
            successor<int>* t = new successor<int>();

            t->push_back(maxLabel);
           // cout << maxLabel << endl;
            result.data->push_back(t);
        }
        // Giải phóng bộ nhớ
        //delete[] distance;
       // delete[] label;
        return result;
    }

    double score(const Dataset &y_test) const
    {
        if (y_test.data->length() <= 0 || this -> data->length()<=0)
        return -1;

    // Kiểm tra dataset hiện tại có rỗng không
    if (this->data->length()!= y_test.data->length())
        return -1;

    int correct_predictions = 0; // Số dự đoán đúng
    int length =  y_test.data->length(); // Lấy độ dài nhỏ nhất để tránh truy cập vượt quá giới hạn

    // Duyệt qua từng cặp nhãn để đếm số dự đoán đúng
    for (int i = 0; i < length; i++)
    {
        // So sánh nhãn trong dataset hiện tại và nhãn trong dataset dự đoán
        if (this->data->get(i) -> get(0) == y_test.data->get(i)-> get(0))
        {
            correct_predictions++;
        }
    }

    // Tính tỷ lệ dự đoán đúng trên tổng số dự đoán và trả về kết quả
    return (static_cast<double>(correct_predictions) / y_test.data -> length());
}
List<List<int>*>* getData() const { return this->data; }
};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset Y_train;
    // You may need to define more
public:
    kNN(int k = 5) : k(k){};
    void fit(const Dataset &X_train, const Dataset &y_train)
    {
        this->X_train = X_train;
        this->Y_train = y_train;
    }
    Dataset predict(const Dataset &X_test)
    {
        return X_test.predict(this->X_train, this->Y_train, this->k);
    }
    double score(const Dataset &y_test, const Dataset &y_pred)
    {
        return y_test.score(y_pred);
    }
};

void train_test_split(Dataset &X, Dataset &Y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    int a,b;
    X.getShape(a,b);
    // cout<<"X: "<<X.getData()->length()<<" "<<"Y: "<<Y.getData()->length()<<"a: "<<a<<" b: "<<b<<endl;
    if (a != Y.getData()->length() || test_size >= 1 || test_size <= 0)
        return;

    double minDouble = 1.0e-13;
    int nRow = X.getData()->length();
    double rowSplit = nRow * (1 - test_size);

    
    rowSplit = floor(rowSplit);

    X_train = X.extract(0, rowSplit - 1, 0, -1);
    X_test = X.extract(rowSplit, -1, 0, -1);
    
//    cout << " nhan biet"<<X_train.getData()->length();
   if (X_train.getData()->length()==0)
   {
    Y_train=X.extract(0, rowSplit - 1, 0, -1);
    Y_test =X.extract(0, rowSplit - 1, 0, -1);

   }
   else{
   
    Y_train = Y.extract(0, rowSplit - 1, 0, -1);
    Y_test = Y.extract(rowSplit, -1, 0, -1);
   }
   //cout<<"Ok"   <<  endl;
 
}

// Please add more or modify as needed