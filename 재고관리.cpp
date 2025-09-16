#include <stdio.h>
#include <stdlib.h>

int main()
{
    int product_number; // 상품의 종류 개수 (1~100)

    // 1. 상품 종류 입력
    printf("상품의 종류 개수를 입력하세요 (1 ~ 100): ");
    scanf("%d", &product_number);

    int product_stock_income[101] = { 0 };  // 입고 수량
    int product_stock_sold[101] = { 0 };    // 판매 수량
    int product_stock_current[101] = { 0 }; // 재고 수량

    // 2. 입고 수량 입력
    printf("\n각 상품의 입고 수량을 입력하세요.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("상품 ID %d 입고 수량: ", i);
        scanf("%d", &product_stock_income[i]);

        // 현재 재고 수량 새로고침
        product_stock_current[i] = product_stock_income[i];
    }

    // 3. 판매 수량 입력
    printf("\n각 상품의 판매 수량을 입력하세요.\n");
    for (int i = 1; i <= product_number; i++)
    {
        printf("상품 ID %d 판매 수량: ", i);
        scanf("%d", &product_stock_sold[i]);

        // 현재 재고 수량 새로고침
        product_stock_current[i] -= product_stock_sold[i];
    }

    // 4. 특정 상품 재고 확인
    int specific_product_stock;
    printf("\n재고를 확인할 상품의 ID를 입력하세요 (1 ~ %d): ", product_number);
    scanf("%d", &specific_product_stock);
    // 특정 상품 재고 출력
    printf("\n상품 ID %d의 현재 재고: %d개\n", specific_product_stock, product_stock_current[specific_product_stock]);

    // 5. 전체 재고 수량 확인
    int total_stock = 0;
    for (int i = 1; i <= product_number; i++)
    {
        total_stock += product_stock_current[i];
    }
    // 전체 재고 수량 출력
    printf("전체 재고 수량: %d개\n", total_stock);

    return 0;
}