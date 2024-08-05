#include "packet.h"

unsigned char olusturalacak_paket[59];

unsigned char check_sum_hesapla(){
    int check_sum = 0;
    
    for(int i = 4; i < 56; i++){
        check_sum += olusturalacak_paket[i];
    }
    
    return (unsigned char) (check_sum % 256); 
}

void addDataPacket(BME_280_t* BME, dso32_struct_t* DSO){//, GPS_t*	GPS){    
  olusturalacak_paket[0] = 0xFF; // Sabit
  olusturalacak_paket[1] = 0xFF; // Sabit
  olusturalacak_paket[2] = 0x54; // Sabit
  olusturalacak_paket[3] = 0x52; // Sabit

  olusturalacak_paket[4] = 0;   // Takim ID = 0
  olusturalacak_paket[5] = 0; // Sayac degeri = 0

  FLOAT32_UINT8_DONUSTURUCU irtifa_float32_uint8_donusturucu;
  irtifa_float32_uint8_donusturucu.sayi = BME->altitude; // Irtifa degerinin atamasini yapiyoruz.
  olusturalacak_paket[6] = irtifa_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[7] = irtifa_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[8] = irtifa_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[9] = irtifa_float32_uint8_donusturucu.array[3];

  float roket_gps_irtifa = ((rand() % 1000) / 10.0) + 1000.0; // 1000.0 ile 1100.0 arasında rastgele
  FLOAT32_UINT8_DONUSTURUCU roket_gps_irtifa_float32_uint8_donusturucu;
  roket_gps_irtifa_float32_uint8_donusturucu.sayi = roket_gps_irtifa; // Roket GPS Irtifa degerinin atamasini yapiyoruz.
  olusturalacak_paket[10] = roket_gps_irtifa_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[11] = roket_gps_irtifa_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[12] = roket_gps_irtifa_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[13] = roket_gps_irtifa_float32_uint8_donusturucu.array[3];

   // Roket Enlem
  float roket_enlem = ((rand() % 1000) / 10000.0) + 39.9; // 39.9000 ile 39.9999 arasında rastgele
  FLOAT32_UINT8_DONUSTURUCU roket_enlem_float32_uint8_donusturucu;
  roket_enlem_float32_uint8_donusturucu.sayi = roket_enlem; // Roket enlem degerinin atamasini yapiyoruz.
  olusturalacak_paket[14] = roket_enlem_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[15] = roket_enlem_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[16] = roket_enlem_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[17] = roket_enlem_float32_uint8_donusturucu.array[3];

  // Roket Boylam
  float roket_boylam = ((rand() % 1000) / 10000.0) + 32.8; // 32.8000 ile 32.8999 arasında rastgele
  FLOAT32_UINT8_DONUSTURUCU roket_boylam_irtifa_float32_uint8_donusturucu;
  roket_boylam_irtifa_float32_uint8_donusturucu.sayi = roket_boylam; // Roket boylam degerinin atamasini yapiyoruz.
  olusturalacak_paket[18] = roket_boylam_irtifa_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[19] = roket_boylam_irtifa_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[20] = roket_boylam_irtifa_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[21] = roket_boylam_irtifa_float32_uint8_donusturucu.array[3];


  FLOAT32_UINT8_DONUSTURUCU jiroskop_x_float32_uint8_donusturucu;
  jiroskop_x_float32_uint8_donusturucu.sayi = DSO->gyro_x; // Jiroskop X degerinin atamasini yapiyoruz.
  olusturalacak_paket[22] = jiroskop_x_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[23] = jiroskop_x_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[24] = jiroskop_x_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[25] = jiroskop_x_float32_uint8_donusturucu.array[3];

  FLOAT32_UINT8_DONUSTURUCU jiroskop_y_float32_uint8_donusturucu;
  jiroskop_y_float32_uint8_donusturucu.sayi = DSO->gyro_y; // Jiroskop Y degerinin atamasini yapiyoruz.
  olusturalacak_paket[26] = jiroskop_y_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[27] = jiroskop_y_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[28] = jiroskop_y_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[29] = jiroskop_y_float32_uint8_donusturucu.array[3];

  FLOAT32_UINT8_DONUSTURUCU jiroskop_z_float32_uint8_donusturucu;
  jiroskop_z_float32_uint8_donusturucu.sayi = DSO->gyro_z; // Jiroskop Z degerinin atamasini yapiyoruz.
  olusturalacak_paket[30] = jiroskop_z_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[31] = jiroskop_z_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[32] = jiroskop_z_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[33] = jiroskop_z_float32_uint8_donusturucu.array[3];

  FLOAT32_UINT8_DONUSTURUCU ivme_x_float32_uint8_donusturucu;
  ivme_x_float32_uint8_donusturucu.sayi = DSO->acc_x; // Ivme X degerinin atamasini yapiyoruz.
  olusturalacak_paket[34] = ivme_x_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[35] = ivme_x_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[36] = ivme_x_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[37] = ivme_x_float32_uint8_donusturucu.array[3];

  FLOAT32_UINT8_DONUSTURUCU ivme_y_float32_uint8_donusturucu;
  ivme_y_float32_uint8_donusturucu.sayi = DSO->acc_y; // Ivme Y degerinin atamasini yapiyoruz.
  olusturalacak_paket[38] = ivme_y_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[39] = ivme_y_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[40] = ivme_y_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[41] = ivme_y_float32_uint8_donusturucu.array[3];

  FLOAT32_UINT8_DONUSTURUCU ivme_z_float32_uint8_donusturucu;
  ivme_z_float32_uint8_donusturucu.sayi = DSO->acc_z; // Ivme Z degerinin atamasini yapiyoruz.
  olusturalacak_paket[42] = ivme_z_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[43] = ivme_z_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[44] = ivme_z_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[45] = ivme_z_float32_uint8_donusturucu.array[3];

  FLOAT32_UINT8_DONUSTURUCU aci_float32_uint8_donusturucu;
  aci_float32_uint8_donusturucu.sayi = DSO->theta; // Aci degerinin atamasini yapiyoruz.
  olusturalacak_paket[46] = aci_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[47] = aci_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[48] = aci_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[49] = aci_float32_uint8_donusturucu.array[3];

  FLOAT32_UINT8_DONUSTURUCU sicaklik_float32_uint8_donusturucu;
  sicaklik_float32_uint8_donusturucu.sayi = BME->temperature; // Sicaklik degerinin atamasini yapiyoruz.
  olusturalacak_paket[50] = sicaklik_float32_uint8_donusturucu.array[0]; 
  olusturalacak_paket[51] = sicaklik_float32_uint8_donusturucu.array[1];
  olusturalacak_paket[52] = sicaklik_float32_uint8_donusturucu.array[2];
  olusturalacak_paket[53] = sicaklik_float32_uint8_donusturucu.array[3];

  //NEM
  olusturalacak_paket[54] = BME->humidity; // Nem degerinin atamasini yapiyoruz

  olusturalacak_paket[55] = DSO->durum; // Durum bilgisi = Iki parasut de tetiklenmedi
    
  olusturalacak_paket[56] = check_sum_hesapla(); // Check_sum = check_sum_hesapla();
  olusturalacak_paket[57] = 0x0D; // Sabit
  olusturalacak_paket[58] = 0x0A;
}