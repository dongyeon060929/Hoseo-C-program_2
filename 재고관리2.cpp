#include <stdio.h>
#include <stdlib.h>

int main()
{
    int product_number; // 상품 종류 개수 

    // 1. 상품 종류 입력
    printf("상품의 종류 개수를 입력하세요 (1 ~ 100): ");
    scanf("%d", &product_number);

    int product_stock_income[101] = { 0 };   // 입고 수량
    int product_stock_sold[101] = { 0 };     // 판매 수량
    int product_stock_current[101] = { 0 };  // 재고 수량

    // 2. 입고 수량 입력
    printf("\n각 상품의 입고 수량을 입력하세요.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("상품 ID %d 입고 수량: ", i);
        scanf("%d", &product_stock_income[i]);

        // 초기 재고 = 입고 수량
        product_stock_current[i] = product_stock_income[i];
    }

    // 3. 판매 수량 입력
    printf("\n각 상품의 판매 수량을 입력하세요.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("상품 ID %d 판매 수량: ", i);
        scanf("%d", &product_stock_sold[i]);

        // 재고 계산
        product_stock_current[i] -= product_stock_sold[i];
        if (product_stock_current[i] < 0) product_stock_current[i] = 0; // 음수 방지
    }

    // 4. 모든 상품의 재고 수량 출력
    printf("\n ----- 상품별 재고 현황 ----- \n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("상품 ID %d - 재고 : %d개\n", i, product_stock_current[i]);
    }

    // 5. 전체 판매량 계산
    int total_sold = 0, total_income = 0; // 전체 판매량
    for (int i = 1; i <= product_number; i++)
    {
        total_sold += product_stock_sold[i];
        total_income += product_stock_income[i];
    }
    printf("\n전체 판매량: %d개\n", total_sold);

    // 6. 전체 판매율 계산
    double sales_rate = 0; // 판매
    if (total_income > 0)
        sales_rate = (double)total_sold / total_income * 100;
    printf("전체 판매율: %.2f%%\n", sales_rate);

    // 7. 최대/최소 판매량 상품
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

    printf("최대 판매량 상품: ID %d (판매 %d개)\n", max_id, max_sold);
    printf("최소 판매량 상품: ID %d (판매 %d개)\n", min_id, min_sold);

    // 8. 재고 부족 경고
    printf("\n===== 재고 부족 경고 =====\n");
    int warning_count = 0;
    for (int i = 1; i <= product_number; i++)
    {
        if (product_stock_current[i] <= 2)
        {
            printf("?? 상품 ID %d의 재고가 부족합니다! (재고: %d개)\n", i, product_stock_current[i]);
            warning_count++;
        }
    }
    if (warning_count == 0)
        printf("모든 상품의 재고가 충분합니다.\n");

    return 0;
}
