#include <stdio.h>
#include <math.h>

struct DeviceUnoptimized {
    char status;
    // 3 bytes padding
    float voltage;
    char device_type;
    // 3 bytes padding
    float current;
    char active_flag;
    // 3 bytes padding
    float power;
    int duration_min;
};

struct DeviceOptimized {
    float voltage;
    float current;
    float power;
    int duration_min;
    char status;
    char device_type;
    char active_flag;
};

int main() {
    printf(" SO SANH KICH THUOC BO NHO STRUCT (MEMORY ALIGNMENT) \n");
    printf("Kich thuoc struct chua toi uu (sizeof): %zu bytes\n", sizeof(struct DeviceUnoptimized));
    printf("Kich thuoc struct da toi uu (sizeof):   %zu bytes\n", sizeof(struct DeviceOptimized));
    printf("Dung luong RAM tiet kiem duoc:         %zu bytes (~28.6%%)\n\n", 
           sizeof(struct DeviceUnoptimized) - sizeof(struct DeviceOptimized));

    struct DeviceOptimized dev;
    dev.device_type = 'A';
    dev.active_flag = 1;

    printf("=== NHAP THONG SO THIET BI GIAM SAT DIEN NANG ===\n");
    printf("Nhap dien ap U (Volt): ");
    if (scanf("%f", &dev.voltage) != 1) { return 1; }

    printf("Nhap dong dien I (Ampere): ");
    if (scanf("%f", &dev.current) != 1) { return 1; }

    printf("Nhap cong su?t do P (Watt): ");
    if (scanf("%f", &dev.power) != 1) { return 1; }

    printf("Nhap thoi gian hoat dong t (phut): ");
    if (scanf("%d", &dev.duration_min) != 1) { return 1; }

    printf("Nhap trang thai thiet bi (0: Tat, 1: Bat): ");
    int temp_status;
    if (scanf("%d", &temp_status) != 1) { return 1; }
    dev.status = (char)temp_status;

    if (dev.voltage <= 0.0f || dev.current < 0.0f || dev.power < 0.0f || dev.duration_min < 0 || (dev.status != 0 && dev.status != 1)) {
        printf("\n[LOI HE THONG] Phat hien du lieu dau vao bat hop ly hoac loi cam bien!\n");
        printf("Kiem tra: U > 0 (nhan: %.2f), I >= 0 (nhan: %.2f), P >= 0 (nhan: %.2f), t >= 0 (nhan: %d), Status in {0,1} (nhan: %d).\n",
               dev.voltage, dev.current, dev.power, dev.duration_min, dev.status);
        return 0;
    }

    printf("\n=== KET QUA PHAN TICH AN TOAN DIEN & NGHIEP VU ===\n");

    float p_calc = dev.voltage * dev.current;
    printf("- Cong suat ly thuyet (P_calc = U * I): %.2f W\n", p_calc);

    if (p_calc > 0.0f) {
        float diff_ratio = fabsf(dev.power - p_calc) / p_calc;
        if (diff_ratio > 0.05f) {
            printf("[CANH BAO] Cam bien cong suat bao sai lech qua 5%% so voi ly thuyet! (Sai lech: %.1f%%)\n", diff_ratio * 100.0f);
        } else {
            printf("[AN TOAN] Cam bien cong suat hoat d?ng chính xác (sai lech <= 5%%).\n");
        }
    } else {
        if (dev.power > 0.1f) {
            printf("[CANH BAO] Cam bien cong suat bao sai lech (P_calc = 0 nhung P > 0)!\n");
        }
    }

    if (dev.current > 30.0f || dev.power > 6600.0f) {
        printf("[CANH BAO KHAN CAP] QUA TAI NGUY HIEM! (Dong dien: %.2f A, Cong suat: %.2f W)\n", dev.current, dev.power);
    } else {
        printf("[AN TOAN] Muc tai dien nam trong nguong cho phep.\n");
    }

    if (dev.status == 0 && dev.current > 0.05f) {
        printf("[CANH BAO AN TOAN] RO RI DIEN HOAC TAI AN! Thiet bi dang TAT nhung van co dong dien ro (I = %.3f A).\n", dev.current);
    } else if (dev.status == 0) {
        printf("[AN TOAN] Trang thai TAT, khong phat hien ro ri dien.\n");
    }

    float hours = (float)dev.duration_min / 60.0f;
    float kwh = (dev.power * hours) / 1000.0f;
    printf("- Thoi gian hoat d?ng: %d phut (%.2f gio)\n", dev.duration_min, hours);
    printf("- Dien nang tieu thu:  %.4f kWh\n", kwh);

    return 0;
}
