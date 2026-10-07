#include <stdio.h>

// Khai bao cau truc SmartDevice (Thiet bi thong minh)
struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status; // 1: Dang bat, 0: Da tat
    float ratedPowerKW;
};

// Khai bao cau truc EnergySensor (Cam bien dien nang & hien dien)
struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    // Khai bao cac bien va struct
    struct SmartDevice device;
    struct EnergySensor sensor;
    float operatingHours;
    float total_kWh;
    float total_cost = 0.0f;

    // --- 1. NHAP DU LIEU TỪ NGUỜI DÙNG ---
    printf("=== NHAP THONG TIN THIET BI ===\n");
    printf("Ma dinh danh thiet bi: ");
    scanf("%d", &device.deviceID);
    printf("Ten thiet bi: ");
    scanf(" %[^\n]", device.deviceName); // Nhap chuoi co khoang trang
    printf("Trang thai hoat dong (1: Bat, 0: Tat): ");
    scanf("%d", &device.status);
    printf("Cong suat dinh muc (kW): ");
    scanf("%f", &device.ratedPowerKW);

    printf("\n=== NHAP THONG TIN CAM BIEN & VAN HANH ===\n");
    printf("Dien ap do duoc (V): ");
    scanf("%f", &sensor.voltageVolts);
    printf("Dong dien do duoc (A): ");
    scanf("%f", &sensor.currentAmperes);
    printf("Thoi gian vang nguoi (phut): ");
    scanf("%d", &sensor.unoccupancyMinutes);
    printf("So gio hoat dong trong thang: ");
    scanf("%f", &operatingHours);
    printf("\n----------------------------------------\n\n");

    // --- 2. KIEM TRA LOI THUONG GAP (DATA VALIDATION) ---
    // Loi 1: Thong so cam bien bat thuong
    if (sensor.voltageVolts < 0 || sensor.currentAmperes < 0 || sensor.unoccupancyMinutes < 0) {
        printf("[LOI HE THONG] Du lieu cam bien bat thuong (Gia tri am). Huy thao tac xu ly!\n");
        return 1; // Ket thuc chuong trinh
    }

    // Loi 2: Thoi gian van hanh khong hop le
    if (operatingHours <= 0 || operatingHours > 744) {
        printf("[LOI HE THONG] Thoi gian van hanh khong hop le (>0 va <=744). Huy tinh toan!\n");
        return 1; // Ket thuc chuong trinh
    }

    // --- 3. XU LY NGHIEP VU THEO THU TU UU TIEN ---
    
    // Uu tien 1: Kiem soat an toan dien (Qua tai > 30A)
    if (sensor.currentAmperes > 30.0f) {
        device.status = 0; // Ngat khien cap
        printf("[CANH BAO NGUY HIEM] Dong dien vuot nguong an toan (%.2f A). DA NGAT THIET BI KAN CAP!\n", sensor.currentAmperes);
    }
    
    // Uu tien 2: Tu dong hoa tiet kiem nang luong (Chi kiem tra khi thiet bi con dang BAT)
    if (device.status == 1 && sensor.unoccupancyMinutes >= 15) {
        device.status = 0; // Tu dong tat
        printf("[TIET KIEM NANG LUONG] Phong trong %d phut. DA TU DONG TAT THIET BI!\n", sensor.unoccupancyMinutes);
    }

    // --- 4. TINH TOAN DIEN NANG & CHI PHI EVN ---
    total_kWh = device.ratedPowerKW * operatingHours;

    // Tinh tien dien luy tien theo 4 bac cua EVN
    if (total_kWh <= 50) {
        // Bac 1: 50 kWh dau tien
        total_cost = total_kWh * 1806;
    } 
    else if (total_kWh <= 100) {
        // Bac 2: Tu 51 - 100
        total_cost = (50 * 1806) + ((total_kWh - 50) * 1866);
    } 
    else if (total_kWh <= 200) {
        // Bac 3: Tu 101 - 200
        total_cost = (50 * 1806) + (50 * 1866) + ((total_kWh - 100) * 2167);
    } 
    else {
        // Bac 4: Tu 201 tro len
        total_cost = (50 * 1806) + (50 * 1866) + (100 * 2167) + ((total_kWh - 200) * 2729);
    }

    // --- 5. IN BAO CAO TONG KET ---
    printf("\n=== BAO CAO HE THONG SMART HOME ===\n");
    printf("- Ma thiet bi      : %d\n", device.deviceID);
    printf("- Ten thiet bi     : %s\n", device.deviceName);
    printf("- Trang thai cuoi  : %s\n", device.status == 1 ? "DANG BAT" : "DA TAT");
    printf("- Tong dien nang   : %.2f kWh\n", total_kWh);
    printf("- Tien dien EVN    : %.0f VND (Chua bao gom VAT)\n", total_cost);
    printf("=======================================\n");

    return 0;
}