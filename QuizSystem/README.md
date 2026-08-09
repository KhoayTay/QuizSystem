# Quiz System Console Application

Đây là hệ thống Console Application hỗ trợ quản lý ngân hàng câu hỏi, đề thi và mô phỏng một phiên làm bài thi trắc nghiệm. Dự án được thiết kế và phát triển bằng C++ (chuẩn C++17), áp dụng các nguyên tắc Lập trình hướng đối tượng (OOP) nhằm đảm bảo mã nguồn dễ bảo trì và mở rộng.

## Cấu trúc thư mục

Dự án được phân tách rõ ràng thành các module theo nguyên tắc Single Responsibility Principle (SRP):

```text
QuizSystem/
├── CMakeLists.txt # File cấu hình biên dịch tự động bằng CMake
├── README.md # Tài liệu hướng dẫn (file này)
├── data/ # Thư mục chứa dữ liệu tĩnh
│   ├── questions.txt # File lưu trữ ngân hàng câu hỏi (định dạng text)
│   └── quizzes.txt # File lưu trữ danh sách đề thi (định dạng text)
├── include/ # Thư mục chứa file định nghĩa Header (.h)
│   ├── Application.h # Điều phối luồng ứng dụng và giao diện người dùng
│   ├── DataFileManager.h # Module đọc/ghi dữ liệu từ file văn bản
│   ├── MCQ.h # Kế thừa lớp Question, xử lý câu trắc nghiệm 4 lựa chọn
│   ├── Question.h # Abstract Base Class cho cấu trúc câu hỏi
│   ├── QuestionBank.h # Quản lý vòng đời và tìm kiếm câu hỏi
│   ├── Quiz.h # Đại diện cho dữ liệu của một bài thi cụ thể
│   ├── QuizEngine.h # Điều khiển vòng đời của một lần làm bài (Attempt)
│   ├── QuizManager.h # Quản lý danh sách các bài thi (Quiz)
│   └── TF.h # Kế thừa lớp Question, xử lý câu hỏi Đúng/Sai (True/False)
└── src/ # Thư mục chứa mã nguồn thực thi (.cpp)
    ├── Application.cpp
    ├── DataFileManager.cpp
    ├── MCQ.cpp
    ├── Question.cpp
    ├── QuestionBank.cpp
    ├── Quiz.cpp
    ├── QuizEngine.cpp
    ├── QuizManager.cpp
    ├── TF.cpp
    └── main.cpp # Điểm khởi chạy của chương trình (khởi tạo dependencies)
```

## Các giới hạn đã chọn (Assumptions & Limitations)

Dự án được xây dựng với một số giả định và giới hạn để phù hợp với ngữ cảnh của một Console Application:

- Môi trường giao diện: Ứng dụng hoạt động 100% trên Command Line Interface (Console). Không có GUI (Graphical User Interface).
- Lưu trữ dữ liệu: Không sử dụng Hệ quản trị cơ sở dữ liệu (DBMS). Dữ liệu được đọc/ghi trực tiếp vào file văn bản thuần túy (.txt). File mới sẽ tự động được tạo và thông báo lỗi rõ ràng nếu đường dẫn không tồn tại, tránh crash chương trình.
- Hệ thống đa luồng: Chương trình chạy trên một luồng (single-thread), không sử dụng multithreading.
- Mô phỏng thi: Hệ thống tập trung vào logic duyệt câu hỏi và chấm điểm; không có đồng hồ đếm ngược (real-time timer).
- Quản lý người dùng: Hệ thống không yêu cầu người dùng đăng nhập hay lưu lịch sử của một phiên làm bài đã diễn ra.
- Xử lý ngoại lệ: Chương trình ưu tiên xử lý luồng bằng vòng lặp và thông báo, không áp dụng exception handling phức tạp.
- Quản lý bộ nhớ: QuestionBank đóng vai trò là chủ sở hữu (owner) và quản lý bộ nhớ của các con trỏ cấp phát động; Quiz và QuizEngine chỉ sử dụng tham chiếu mà không trực tiếp quản lý giải phóng.

## Cách Build và Chạy chương trình

Hệ thống được cấu hình tự động thông qua CMake.

### 1. Yêu cầu môi trường

- Trình biên dịch C++ (ví dụ: GCC, MinGW, Clang) có hỗ trợ chuẩn C++11 trở lên.
- Hệ thống build CMake phiên bản 3.10 trở lên.
- Trình soạn thảo mã (IDE) như Visual Studio Code.

### 2. Các bước Build và Chạy bằng Visual Studio Code

1.  Cài đặt tiện ích mở rộng: Cài đặt hai extension `C/C++` và `CMake Tools` trong VS Code.
2.  Mở thư mục dự án: Mở thư mục chứa file `CMakeLists.txt` (thư mục `QuizSystem` bên trong thư mục lớn) trên VS Code.
3.  Cấu hình CMake: Nhấn tổ hợp phím `Ctrl + Shift + P`, gõ lệnh `CMake: Configure`. Sau đó chọn trình biên dịch (Compiler Kit) GCC/MinGW đang có trên máy của bạn.
4.  Biên dịch: Nhấn nút Build ở thanh trạng thái bên dưới (Status Bar) của VS Code. File thực thi (`QuizSystem.exe`) sẽ được tạo tự động trong thư mục con `build/`.
5.  Chạy ứng dụng: Mở terminal và gõ lệnh thực thi:

```bash
./build/QuizSystem.exe
```

## Định dạng file dữ liệu (Data Format)

Dữ liệu được lưu trữ trong thư mục `data/` với quy tắc phân tách bằng ký tự `|`.

### 1. Ngân hàng câu hỏi (`questions.txt`)

Hỗ trợ hai định dạng câu hỏi

- Multiple Choice Question (MCQ): `MCQ|id|points|prompt|optionA;optionB;optionC;optionD|correctOption`
  _Ví dụ:_ `MCQ|101|2|2 + 2 = ?|3;4;5;6|B`
- True/False Question (TF): `TF|id|points|prompt|correctAnswer`
  _Ví dụ:_ `TF|102|1|C++ supports inheritance|true`

### 2. Danh sách đề thi (`quizzes.txt`)

Mỗi dòng biểu diễn một đề thi chứa danh sách các ID câu hỏi:

- Định dạng: `quizId|title|questionId1,questionId2,...`
  _Ví dụ:_ `201|C++ Basics|101,102`

## Danh sách tính năng hoàn thành (Features)

Hệ thống đã triển khai đầy đủ các yêu cầu chức năng (FR) sau:

### FR-01: Quản lý Question Bank

- Tải câu hỏi từ file vào bộ nhớ, lưu dữ liệu sau khi sửa đổi và lúc tắt chương trình.
- Hiển thị ID, loại, số điểm và nội dung câu hỏi theo định dạng dễ đọc.
- Thêm MCQ hoặc TF và từ chối ID trùng, prompt rỗng, points không hợp lệ hoặc dữ liệu riêng sai quy tắc.
- Cập nhật prompt, points và dữ liệu riêng của một câu hỏi đã tồn tại mà không làm thay đổi ID hoặc loại câu hỏi.
- Xóa câu hỏi theo ID; khi xóa, ID đó cũng được loại khỏi mọi Quiz.
- Tìm theo ID; tìm theo một phần prompt, không phân biệt chữ hoa/chữ thường.

### FR-02: Quản lý Quiz

- Nạp Quiz từ file khi khởi động; lưu lại sau khi thay đổi hoặc trước khi thoát.
- Tạo, đổi tên, xóa và hiển thị danh sách Quiz.
- Thêm câu hỏi vào Quiz bằng ID (chỉ chấp nhận ID tồn tại) và không cho phép lặp lại.
- Xóa câu hỏi khỏi Quiz và hiển thị câu hỏi theo đúng thứ tự đã thêm.

### FR-03: Mô phỏng phiên làm bài

- Chọn Quiz, bắt đầu phiên làm bài và chuyển trạng thái sang IN_PROGRESS.
- Hiển thị câu hỏi hiện tại, các lựa chọn tùy thuộc vào loại câu hỏi và hỗ trợ điều hướng next/previous.
- Cho phép thay đổi đáp án đã nhập khi đang IN_PROGRESS.
- Nộp bài (SUBMITTED), tính tổng điểm (câu chưa trả lời tính là sai) và khóa chỉnh sửa.
- Hiển thị tổng điểm và chi tiết đúng/sai của từng câu sau khi Submit.

### FR-04: Loại câu hỏi và Runtime Polymorphism

- Question là abstract base class; MCQ và TF là hai derived class.
- Cung cấp virtual display() và virtual destructor.
- Quiz Engine gọi display() thông qua Question pointer/reference.

### FR-05 & FR-06: Lưu trữ và Giao diện

- Lưu và khôi phục dữ liệu đúng định dạng; tự động khởi tạo file rỗng nếu chưa tồn tại.
- Bỏ qua dòng sai định dạng, báo lỗi rõ ràng và không crash chương trình.
- Menu phân cấp rõ ràng, bắt lỗi input sai và làm sạch luồng nhập.
