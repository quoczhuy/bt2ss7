# Báo cáo Phân tích và Thiết kế Giải pháp: Module Quản lý Cụm Thiết bị Phòng Thông minh

## 1. Phân tích bài toán (Input / Output)
**Đầu vào (Input):**
*   Thông tin thiết bị (Cấu trúc `SmartDevice`):
    *   `deviceID` (int): Mã định danh thiết bị.
    *   `deviceName` (chuỗi): Tên thiết bị (VD: "Dieu hoa trung tam").
    *   `status` (int): Trạng thái (1 - Bật, 0 - Tắt).
    *   `ratedPowerKW` (float): Công suất định mức (kW).
*   Thông tin cảm biến (Cấu trúc `EnergySensor`):
    *   `voltageVolts` (float): Điện áp (V).
    *   `currentAmperes` (float): Dòng điện (A).
    *   `unoccupancyMinutes` (int): Thời gian vắng người (phút).
*   Dữ liệu vận hành:
    *   `operatingHours` (float): Số giờ hoạt động trong tháng.

**Đầu ra (Output):**
*   Thông báo lỗi nếu dữ liệu đầu vào không hợp lệ (âm hoặc quá giới hạn).
*   Cảnh báo khẩn cấp nếu quá tải dòng điện.
*   Thông báo tiết kiệm năng lượng nếu phòng trống.
*   Báo cáo tổng kết: Trạng thái thiết bị cuối cùng, Tổng điện năng tiêu thụ (kWh), và Tiền điện dự kiến theo bậc thang EVN.

## 2. Đề xuất giải pháp
*   Sử dụng hai cấu trúc `struct SmartDevice` và `struct EnergySensor` để nhóm các thuộc tính dữ liệu liên quan.
*   Sử dụng toán tử dấu chấm (`.`) để trực tiếp truy xuất và cập nhật các thành viên (member) trong struct nhằm thay đổi trạng thái của hệ thống.
*   Xử lý tuần tự theo luồng if-else để đảm bảo các ràng buộc về an toàn dữ liệu (Data Validation) được thực hiện trước khi đi vào tính toán logic nghiệp vụ.

## 3. Thiết kế các bước xử lý logic
*   **Bước 1:** Khai báo cấu trúc và khởi tạo biến. Nhập liệu từ người dùng.
*   **Bước 2:** Kiểm tra tính hợp lệ dữ liệu (Lỗi 1 & Lỗi 2). Nếu cảm biến báo số âm hoặc số giờ vận hành `<= 0` hoặc `> 744`, in thông báo lỗi và kết thúc chương trình (`return 1`).
*   **Bước 3 (An toàn điện):** Kiểm tra `currentAmperes > 30.0`. Nếu đúng, gán `status = 0`, in cảnh báo.
*   **Bước 4 (Tiết kiệm điện):** Nếu thiết bị vẫn đang bật (`status == 1`) VÀ `unoccupancyMinutes >= 15`, gán `status = 0`, in thông báo tự động tắt.
*   **Bước 5:** Tính toán tổng `kWh = ratedPowerKW * operatingHours`.
*   **Bước 6 (Tính tiền điện EVN):** Sử dụng khối lệnh `if - else if` để tính tiền điện lũy tiến theo 4 bậc.
*   **Bước 7:** In báo cáo tổng kết ra màn hình.