#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int product_number; // 상품 종류 개수
    int menu;           // 메뉴 선택 변수

    // 1. 상품 종류 입력
    printf("상품의 종류 개수를 입력하세요 (1 ~ 100): ");
    scanf("%d", &product_number);

    int product_stock_income[101] = { 0 };   // 입고 수량
    int product_stock_sold[101] = { 0 };     // 판매 수량
    int product_stock_current[101] = { 0 };  // 재고 수량
    char product_name[101][50];              // 상품명

    // 기본값 "(미입력)" 설정
    for (int i = 1; i <= product_number; i++)
    {
        strcpy(product_name[i], "(미입력)");
    }

    while (1)
    {
        printf("\n원하는 메뉴를 선택하세요.\n");
        printf("1. 입고\n2. 판매\n3. 상품현황\n4. 상품명 입력\n5. 종료\n");
        printf("선택: ");
        scanf("%d", &menu);

        if (menu == 1) // 입고
        {
            printf("\n<< 입고 수량 입력 >>\n");
            for (int i = 1; i <= product_number; i++)
            {
                int quantity;
                printf("상품 ID %d (%s) 입고 수량: ", i, product_name[i]);
                scanf("%d", &quantity);

                product_stock_income[i] += quantity;
                product_stock_current[i] += quantity;
            }
        }
        else if (menu == 2) // 판매
        {
            printf("\n<< 판매 수량 입력 >>\n");
            for (int i = 1; i <= product_number; i++)
            {
                int quantity;
                printf("상품 ID %d (%s) 판매 수량: ", i, product_name[i]);
                scanf("%d", &quantity);

                product_stock_sold[i] += quantity;
                product_stock_current[i] -= quantity;
                if (product_stock_current[i] < 0) product_stock_current[i] = 0;
            }
        }
        else if (menu == 3) // 상품현황
        {
            printf("\n<< 상품 현황 >>\n");

            printf("재고수량: ");
            for (int i = 1; i <= product_number; i++)
                printf("%d ", product_stock_current[i]);
            printf("\n");

            // 총 판매량, 판매율
            int total_sold = 0, total_income = 0;
            for (int i = 1; i <= product_number; i++)
            {
                total_sold += product_stock_sold[i];
                total_income += product_stock_income[i];
            }
            printf("총 판매량: %d (판매율 %.2f%%)\n", total_sold,
                total_income > 0 ? (double)total_sold / total_income * 100 : 0);

            // 최대 / 최소 판매
            int max_sold = product_stock_sold[1], min_sold = product_stock_sold[1];
            int max_id = 1, min_id = 1;
            for (int i = 2; i <= product_number; i++)
            {
                if (product_stock_sold[i] > max_sold)
                {
                    max_sold = product_stock_sold[i];
                    max_id = i;
                }
                if (product_stock_sold[i] < min_sold)
                {
                    min_sold = product_stock_sold[i];
                    min_id = i;
                }
            }
            printf("가장 많이 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n",
                max_id, product_name[max_id], max_sold);
            printf("가장 적게 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n",
                min_id, product_name[min_id], min_sold);

            // 재고 부족 표시
            for (int i = 1; i <= product_number; i++)
            {
                if (product_stock_current[i] <= 2)
                {
                    printf("상품 ID %d : 상품명 %s 재고부족(%d)\n",
                        i, product_name[i], product_stock_current[i]);
                }
            }
        }
        else if (menu == 4) // 상품명 입력
        {
            printf("\n<< 상품명 입력 메뉴 실행 >>\n");
            for (int i = 1; i <= product_number; i++)
            {
                printf("ID %d 상품명: ", i);
                scanf("%s", product_name[i]);
            }
        }
        else if (menu == 5) // 종료
        {
            printf("\n프로그램을 종료합니다.\n");
            break;
        }
        else
        {
            printf("잘못된 선택입니다. 다시 입력하세요.\n");
        }
    }

    return 0;
}