#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 5 // 프로그램 시작 시 초기 용량
#define MAX_NAME_LEN 50
#define DATA_FILE "products.dat"

typedef struct
{
    char name[MAX_NAME_LEN];    // 상품 이름
    int stock_income;           // 총 입고된 수량
    int stock_sold;             // 총 판매된 수량
    int stock_current;          // 현재 남아있는 재고
    int price;                  // 판매 가격
    long long total_revenue;    // 이 상품으로 벌어들인 총 매출 금액
} Product;

void clear_input_buffer();
void save_data(Product products[], int count);
void load_data(Product** products_ptr, int* max_products_ptr);
void handle_resize(Product** products_ptr, int* max_products_ptr); // 목록 확장 함수
void handle_income(Product products[], int count); // 1. 입고 처리
void handle_sale(Product products[], int count);   // 2. 판매 처리
void handle_individual_info(Product products[], int count); // 3. 개별 상품 정보 조회/수정
void handle_overall_status(Product products[], int count);  // 4. 전체 현황 조회

int main()
{
    int menu;
    int max_products = INITIAL_CAPACITY; 
    Product* products = NULL;

    products = (Product*)calloc(max_products + 1, sizeof(Product));

    if (products == NULL)
    {
        printf("초기 메모리 할당 실패! 프로그램을 종료합니다.\n");
        return 1;
    }

    for (int i = 1; i <= max_products; i++)
    {
        strcpy(products[i].name, "(미입력)");
    }

    printf("? 쇼핑몰 재고 관리 프로그램 시작 ?\n");

    while (1)
    {
        // 메뉴에 8. 상품 목록 확장 추가
        printf("\n1. 입고\n2. 판매\n3. 개별상품정보\n4. 전체현황\n5. 상품저장\n6. 상품불러오기\n7. 종료\n8. 상품 목록 확장\n선택: ");

        if (scanf("%d", &menu) != 1)
        {
            printf("숫자로만 입력해주세요.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (menu)
        {
        case 1: handle_income(products, max_products); break;
        case 2: handle_sale(products, max_products); break;
        case 3: handle_individual_info(products, max_products); break;
        case 4: handle_overall_status(products, max_products); break;
        case 5: save_data(products, max_products); break;
        case 6: load_data(&products, &max_products); break;
        case 7:
            printf("프로그램을 종료합니다.\n");
            free(products); // --- 동적 할당된 메모리 해제 ---
            return 0;
        case 8: handle_resize(&products, &max_products); break; // 8번 메뉴 처리
        default: printf("1부터 8 중 하나를 선택하세요.\n"); break; // 범위 변경
        }
    }
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// (1) 입고 처리 함수
void handle_income(Product products[], int count)
{
    int id, quantity, price;
    printf("\n<< 1. 입고 >>\n상품 ID (1~%d): ", count); 
    if (scanf("%d", &id) != 1 || id < 1 || id > count)
    {
        printf("잘못된 상품 번호입니다.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    if (strcmp(products[id].name, "(미입력)") == 0)
    {
        printf("상품명 입력: ");
        if (fgets(products[id].name, MAX_NAME_LEN, stdin) != NULL)
            products[id].name[strcspn(products[id].name, "\n")] = 0;
    }
    else
    {
        printf("상품명: %s\n", products[id].name);
    }

    printf("입고 수량: ");
    if (scanf("%d", &quantity) != 1 || quantity <= 0)
    {
        printf("수량은 1개 이상이어야 합니다.\n"); clear_input_buffer(); return;
    }
    printf("판매 가격: ");
    if (scanf("%d", &price) != 1 || price < 0)
    {
        printf("가격은 0원 이상이어야 합니다.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    products[id].stock_income += quantity;
    products[id].stock_current += quantity;
    products[id].price = price;
    printf("ID %d (%s)에 %d개 입고 완료. 현재 재고: %d\n", id, products[id].name, quantity, products[id].stock_current);
}

// (2) 판매 처리 함수
void handle_sale(Product products[], int count)
{
    int id, quantity;
    printf("\n<< 2. 판매 >>\n상품 ID (1~%d): ", count); 
    if (scanf("%d", &id) != 1 || id < 1 || id > count)
    {
        printf("잘못된 상품 번호입니다.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    if (strcmp(products[id].name, "(미입력)") == 0)
    {
        printf("상품이 등록되지 않았습니다.\n"); return;
    }

    printf("상품명: %s, 현재 재고: %d\n판매 수량: ", products[id].name, products[id].stock_current);
    if (scanf("%d", &quantity) != 1 || quantity <= 0)
    {
        printf("수량은 1개 이상이어야 합니다.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    if (quantity > products[id].stock_current)
    {
        printf("재고 부족! 현재 재고: %d개\n", products[id].stock_current); return;
    }
    if (products[id].price == 0)
    {
        printf("판매 가격이 0원입니다.\n"); return;
    }

    products[id].stock_sold += quantity;
    products[id].stock_current -= quantity;
    products[id].total_revenue += (long long)quantity * products[id].price;

    printf("ID %d (%s) %d개 판매 완료. 판매 금액: %lld원\n", id, products[id].name, quantity, (long long)quantity * products[id].price);
    if (products[id].stock_current == 0) printf("재고 소진 알림.\n");
}

// (3) 개별 상품 정보 조회/수정 함수
void handle_individual_info(Product products[], int count)
{
    int id, sub_menu;
    printf("\n<< 3. 개별상품정보 >>\n1. 상품명 수정\n2. 현황 조회\n선택: ");
    if (scanf("%d", &sub_menu) != 1)
    {
        printf("선택 오류.\n"); clear_input_buffer(); return;
    }

    printf("상품 ID (1~%d): ", count);
    if (scanf("%d", &id) != 1 || id < 1 || id > count)
    {
        printf("잘못된 ID.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    if (sub_menu == 1)
    {
        printf("새 상품명 입력 (현재: %s): ", products[id].name);
        if (fgets(products[id].name, MAX_NAME_LEN, stdin) != NULL)
            products[id].name[strcspn(products[id].name, "\n")] = 0;
        printf("상품명이 '%s'로 수정되었습니다.\n", products[id].name);
    }
    else if (sub_menu == 2)
    {
        if (strcmp(products[id].name, "(미입력)") == 0)
        {
            printf("상품이 미등록입니다.\n"); return;
        }
        printf("\n--- ID %d (%s) 현황 ---\n", id, products[id].name);
        printf("판매 가격\t: %d원\n입고 수량\t: %d개\n판매 수량\t: %d개\n현재 재고\t: %d개\n총 판매 금액\t: %lld원\n",
            products[id].price, products[id].stock_income, products[id].stock_sold,
            products[id].stock_current, products[id].total_revenue);
    }
    else
    {
        printf(" 잘못된 선택입니다.\n");
    }
}

// (4) 전체 현황 조회 함수
void handle_overall_status(Product products[], int count)
{
    printf("\n<< 4. 전체 상품 현황 >>\n");
    printf("ID | 상품명 | 재고 | 입고 | 판매 | 가격 | 총매출\n");
    printf("----------------------------------------------------------\n");

    long long overall_revenue = 0;
    int total_sold = 0, total_income = 0;
    int max_id = 0, min_id = 0;

    for (int i = 1; i <= count; i++)
    {
        if (strcmp(products[i].name, "(미입력)") == 0) continue;

        printf("%-3d| %-7s | %-4d | %-4d | %-4d | %-5d | %-10lld\n",
            i, products[i].name, products[i].stock_current, products[i].stock_income,
            products[i].stock_sold, products[i].price, products[i].total_revenue);

        overall_revenue += products[i].total_revenue;
        total_sold += products[i].stock_sold;
        total_income += products[i].stock_income;

        if (max_id == 0)
        {
            max_id = min_id = i;
        }
        else
        {
            if (products[i].stock_sold > products[max_id].stock_sold) max_id = i;
            if (products[i].stock_sold < products[min_id].stock_sold) min_id = i;
        }
    }

    printf("----------------------------------------------------------\n");
    printf("총 입고: %d, 총 판매: %d\n", total_income, total_sold);
    printf("총 판매율: %.2f%%\n", total_income > 0 ? (double)total_sold / total_income * 100 : 0.0);
    printf("총 판매 금액: %lld 원\n", overall_revenue);

    if (max_id != 0)
    {
        printf("최다 판매: ID %d (%s), %d개\n", max_id, products[max_id].name, products[max_id].stock_sold);
        printf("최소 판매: ID %d (%s), %d개\n", min_id, products[min_id].name, products[min_id].stock_sold);
    }
    for (int i = 1; i <= count; i++)
    {
        if (products[i].stock_current <= 2 && strcmp(products[i].name, "(미입력)") != 0)
            printf("재고 부족: ID %d (%s), 재고: %d개\n", i, products[i].name, products[i].stock_current);
    }
}

// (5) 상품 저장 함수 (바이너리 파일에 저장)
void save_data(Product products[], int count)
{
    FILE* fp = fopen(DATA_FILE, "wb");
    if (fp == NULL)
    {
        perror("? 파일 저장 실패"); return;
    }

    if (fwrite(&count, sizeof(int), 1, fp) != 1)
    {
        printf("개수 저장 실패.\n");
        fclose(fp);
        return;
    }

    size_t written = fwrite(&products[1], sizeof(Product), count, fp);

    if (written == (size_t)count)
    {
        printf("상품 정보 %d개가 '%s' 파일에 성공적으로 저장되었습니다.\n", count, DATA_FILE);
    }
    else
    {
        printf("저장 중 오류 발생.\n");
    }
    fclose(fp);
}

// (6) 상품 불러오기 함수 (바이너리 파일에서 읽기)
void load_data(Product** products_ptr, int* max_products_ptr)
{
    FILE* fp = fopen(DATA_FILE, "rb");
    if (fp == NULL)
    {
        perror("파일 불러오기 실패 (저장된 파일이 없음)");
        return;
    }

    int file_count = 0;
    if (fread(&file_count, sizeof(int), 1, fp) != 1)
    {
        printf("파일 형식 오류: 상품 개수를 읽을 수 없습니다.\n");
        fclose(fp);
        return;
    }

    if (file_count <= 0)
    {
        printf("파일에 저장된 상품이 없습니다.\n");
        fclose(fp);
        return;
    }

    Product* new_products = (Product*)realloc(*products_ptr, (file_count + 1) * sizeof(Product));

    if (new_products == NULL)
    {
        printf("데이터 로드 중 메모리 재할당 실패!\n");
        fclose(fp);
        return;
    }

    *products_ptr = new_products;
    *max_products_ptr = file_count;

    size_t read = fread(&(*products_ptr)[1], sizeof(Product), file_count, fp);

    if (read == (size_t)file_count)
    {
        printf("상품 정보 %d개를 '%s' 파일에서 성공적으로 불러왔습니다.\n", file_count, DATA_FILE);
    }
    else
    {
        printf("파일 내용 오류. 일부 데이터만 불러왔습니다.\n");
    }
    fclose(fp);
}

// (8) 상품 목록 확장 함수
void handle_resize(Product** products_ptr, int* max_products_ptr)
{
    int old_capacity = *max_products_ptr;
    int new_capacity = 0;

    printf("\n<< 8. 상품 목록 확장 >>\n");
    printf("현재 상품 목록 용량: %d\n", old_capacity);
    printf("새로운 용량 입력 (현재보다 커야 함): ");

    if (scanf("%d", &new_capacity) != 1 || new_capacity <= old_capacity)
    {
        printf("잘못된 용량입니다. (현재 용량 %d보다 커야 합니다.)\n", old_capacity);
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    Product* new_products = (Product*)realloc(*products_ptr, (new_capacity + 1) * sizeof(Product));

    if (new_products == NULL)
    {
        printf("메모리 확장에 실패했습니다! (기존 데이터는 유지됩니다)\n");
        return;
    }

    // 새로 할당된 영역(old_capacity + 1 부터)을 초기화
    for (int i = old_capacity + 1; i <= new_capacity; i++)
    {
        memset(&new_products[i], 0, sizeof(Product)); 
        strcpy(new_products[i].name, "(미입력)");
    }

    // main의 포인터와 변수 값을 업데이트
    *products_ptr = new_products;
    *max_products_ptr = new_capacity;

    printf("상품 목록 용량이 %d에서 %d로 성공적으로 확장되었습니다.\n", old_capacity, new_capacity);
}