//쇼핑몰 프로젝트
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_NAME_LEN 50

int main()
{
    int product_number = MAX_PRODUCTS; // 상품 종류 고정
    int menu;

    // 상품 정보 배열
    int product_stock_income[MAX_PRODUCTS + 1] = { 0 };
    int product_stock_sold[MAX_PRODUCTS + 1] = { 0 };
    int product_stock_current[MAX_PRODUCTS + 1] = { 0 };
    int product_price[MAX_PRODUCTS + 1] = { 0 };
    long long product_total_revenue[MAX_PRODUCTS + 1] = { 0 };
    char product_name[MAX_PRODUCTS + 1][MAX_NAME_LEN];

    // 상품명 기본값 설정
    for (int i = 1; i <= MAX_PRODUCTS; i++) 
    {
        strcpy(product_name[i], "(미입력)");
    }

    while (1) 
    {
        printf("\n원하는 메뉴를 선택하세요.\n");
        printf("1. 입고\n2. 판매\n3. 개별상품정보\n4. 전체현황\n5. 종료\n");
        printf("선택: ");
        if (scanf("%d", &menu) != 1) 
        {
            printf("잘못된 입력입니다. 프로그램을 종료합니다.\n");
            break;
        }

        // 1. 입고
        if (menu == 1) 
        {
            int id, quantity, price;
            printf("\n<< 입고 메뉴 실행 (상품ID, 수량, 가격 입력) >>\n");
            printf("상품 ID를 입력하세요 (1 ~ %d): ", product_number);
            scanf("%d", &id);

            if (id < 1 || id > product_number) 
            {
                printf("잘못된 상품 ID입니다.\n");
                continue;
            }
            if (strcmp(product_name[id], "(미입력)") == 0) 
            {
                printf("상품명이 등록되지 않은 상품입니다. 먼저 상품명을 입력하세요.\n");
                continue;
            }

            printf("상품명: %s\n", product_name[id]);
            printf("입고 수량: ");
            scanf("%d", &quantity);
            printf("판매 가격: ");
            scanf("%d", &price);

            product_stock_income[id] += quantity;
            product_stock_current[id] += quantity;
            product_price[id] = price;

            printf("상품 ID %d (%s)에 %d개 입고, 가격: %d원\n",
                id, product_name[id], quantity, price);
        }

        // 2. 판매
        else if (menu == 2) 
        {
            int id, quantity;
            printf("\n<< 판매 메뉴 실행 (상품ID, 판매수량 입력) >>\n");
            printf("상품 ID를 입력하세요 (1 ~ %d): ", product_number);
            scanf("%d", &id);

            if (id < 1 || id > product_number) 
            {
                printf("잘못된 상품 ID입니다.\n");
                continue;
            }
            if (strcmp(product_name[id], "(미입력)") == 0)
            {
                printf("상품명이 등록되지 않은 상품입니다. 먼저 상품명을 입력하세요.\n");
                continue;
            }

            printf("상품명: %s, 현재 재고: %d\n", product_name[id], product_stock_current[id]);
            printf("판매 수량: ");
            scanf("%d", &quantity);

            if (quantity <= 0) 
            {
                printf("판매 수량은 1개 이상이어야 합니다.\n");
                continue;
            }

            if (quantity > product_stock_current[id]) 
            {
                printf("재고 부족! 현재 재고: %d개\n", product_stock_current[id]);
                continue;
            }

            product_stock_sold[id] += quantity;
            product_stock_current[id] -= quantity;
            product_total_revenue[id] += (long long)quantity * product_price[id];

            printf("상품 ID %d (%s) %d개 판매, 판매 금액: %lld원\n",
                id, product_name[id], quantity, (long long)quantity * product_price[id]);

            if (product_stock_current[id] == 0) 
            {
                printf("※ 재고 소진: 상품 ID %d (%s)\n", id, product_name[id]);
            }
        }

        // 3. 개별상품정보
        else if (menu == 3) 
        {
            int id, sub_menu;
            printf("\n<< 개별상품정보 >>\n");
            printf("1. 상품명 입력/수정\n2. 개별 현황 조회\n선택: ");
            scanf("%d", &sub_menu);

            printf("상품 ID를 입력하세요 (1 ~ %d): ", product_number);
            scanf("%d", &id);

            if (id < 1 || id > product_number) 
            {
                printf("잘못된 상품 ID입니다.\n");
                continue;
            }

            if (sub_menu == 1) 
            {
                printf("새 상품명 입력: ");
                scanf("%s", product_name[id]);
                printf("상품명이 '%s'로 등록되었습니다.\n", product_name[id]);
            }
            else if (sub_menu == 2) 
            {
                if (strcmp(product_name[id], "(미입력)") == 0) 
                {
                    printf("상품명이 아직 등록되지 않았습니다.\n");
                    continue;
                }
                printf("\n--- 상품 ID %d 현황 ---\n", id);
                printf("상품명        : %s\n", product_name[id]);
                printf("판매 가격     : %d 원\n", product_price[id]);
                printf("입고 수량     : %d 개\n", product_stock_income[id]);
                printf("판매 수량     : %d 개\n", product_stock_sold[id]);
                printf("재고 수량     : %d 개\n", product_stock_current[id]);
                printf("총 판매 금액  : %lld 원\n", product_total_revenue[id]);
            }
            else 
            {
                printf("잘못된 선택입니다.\n");
            }
        }

        // 4. 전체현황
        else if (menu == 4) 
        {
            printf("\n<< 전체 상품 현황 >>\n");
            printf("상품ID | 상품명     | 재고 | 입고 | 판매 | 가격 | 총판매금액\n");
            printf("----------------------------------------------------------\n");

            long long overall_revenue = 0;
            int total_sold = 0, total_income = 0;

            for (int i = 1; i <= product_number; i++) 
            {
                printf("%-7d | %-10s | %-4d | %-4d | %-4d | %-5d | %-10lld\n",
                    i, product_name[i], product_stock_current[i],
                    product_stock_income[i], product_stock_sold[i],
                    product_price[i], product_total_revenue[i]);

                overall_revenue += product_total_revenue[i];
                total_sold += product_stock_sold[i];
                total_income += product_stock_income[i];
            }

            printf("----------------------------------------------------------\n");
            printf("총 입고량: %d, 총 판매량: %d\n", total_income, total_sold);
            printf("총 판매율: %.2f%%\n", total_income > 0 ? (double)total_sold / total_income * 100 : 0.0);
            printf("총 판매 금액: %lld 원\n", overall_revenue);

            // 최대/최소 판매 상품
            int max_id = 1, min_id = 1;
            for (int i = 2; i <= product_number; i++) 
            {
                if (product_stock_sold[i] > product_stock_sold[max_id]) max_id = i;
                if (product_stock_sold[i] < product_stock_sold[min_id]) min_id = i;
            }

            printf("최다 판매 상품: ID %d (%s), 판매량 %d\n",
                max_id, product_name[max_id], product_stock_sold[max_id]);
            printf("최소 판매 상품: ID %d (%s), 판매량 %d\n",
                min_id, product_name[min_id], product_stock_sold[min_id]);

            // 재고 부족 알림
            for (int i = 1; i <= product_number; i++) 
            {
                if (product_stock_current[i] <= 2) 
                {
                    printf("※ 재고 부족: 상품 ID %d (%s), 재고: %d개\n",
                        i, product_name[i], product_stock_current[i]);
                }
            }
        }

        // 5. 종료
        else if (menu == 5) 
        {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        // 잘못된 입력
        else 
        {
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
        }
    }

    return 0;
}