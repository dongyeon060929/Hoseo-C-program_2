#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int product_number; // ��ǰ ���� ����
    int menu;           // �޴� ���� ����

    // 1. ��ǰ ���� �Է�
    printf("��ǰ�� ���� ������ �Է��ϼ��� (1 ~ 100): ");
    scanf("%d", &product_number);

    int product_stock_income[101] = { 0 };   // �԰� ����
    int product_stock_sold[101] = { 0 };     // �Ǹ� ����
    int product_stock_current[101] = { 0 };  // ��� ����
    char product_name[101][50];              // ��ǰ��

    // �⺻�� "(���Է�)" ����
    for (int i = 1; i <= product_number; i++)
    {
        strcpy(product_name[i], "(���Է�)");
    }

    while (1)
    {
        printf("\n���ϴ� �޴��� �����ϼ���.\n");
        printf("1. �԰�\n2. �Ǹ�\n3. ��ǰ��Ȳ\n4. ��ǰ�� �Է�\n5. ����\n");
        printf("����: ");
        scanf("%d", &menu);

        if (menu == 1) // �԰�
        {
            printf("\n<< �԰� ���� �Է� >>\n");
            for (int i = 1; i <= product_number; i++)
            {
                int quantity;
                printf("��ǰ ID %d (%s) �԰� ����: ", i, product_name[i]);
                scanf("%d", &quantity);

                product_stock_income[i] += quantity;
                product_stock_current[i] += quantity;
            }
        }
        else if (menu == 2) // �Ǹ�
        {
            printf("\n<< �Ǹ� ���� �Է� >>\n");
            for (int i = 1; i <= product_number; i++)
            {
                int quantity;
                printf("��ǰ ID %d (%s) �Ǹ� ����: ", i, product_name[i]);
                scanf("%d", &quantity);

                product_stock_sold[i] += quantity;
                product_stock_current[i] -= quantity;
                if (product_stock_current[i] < 0) product_stock_current[i] = 0;
            }
        }
        else if (menu == 3) // ��ǰ��Ȳ
        {
            printf("\n<< ��ǰ ��Ȳ >>\n");

            printf("������: ");
            for (int i = 1; i <= product_number; i++)
                printf("%d ", product_stock_current[i]);
            printf("\n");

            // �� �Ǹŷ�, �Ǹ���
            int total_sold = 0, total_income = 0;
            for (int i = 1; i <= product_number; i++)
            {
                total_sold += product_stock_sold[i];
                total_income += product_stock_income[i];
            }
            printf("�� �Ǹŷ�: %d (�Ǹ��� %.2f%%)\n", total_sold,
                total_income > 0 ? (double)total_sold / total_income * 100 : 0);

            // �ִ� / �ּ� �Ǹ�
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
            printf("���� ���� �Ǹŵ� ��ǰ : ID %d, ��ǰ�� : %s, �Ǹŷ� %d\n",
                max_id, product_name[max_id], max_sold);
            printf("���� ���� �Ǹŵ� ��ǰ : ID %d, ��ǰ�� : %s, �Ǹŷ� %d\n",
                min_id, product_name[min_id], min_sold);

            // ��� ���� ǥ��
            for (int i = 1; i <= product_number; i++)
            {
                if (product_stock_current[i] <= 2)
                {
                    printf("��ǰ ID %d : ��ǰ�� %s ������(%d)\n",
                        i, product_name[i], product_stock_current[i]);
                }
            }
        }
        else if (menu == 4) // ��ǰ�� �Է�
        {
            printf("\n<< ��ǰ�� �Է� �޴� ���� >>\n");
            for (int i = 1; i <= product_number; i++)
            {
                printf("ID %d ��ǰ��: ", i);
                scanf("%s", product_name[i]);
            }
        }
        else if (menu == 5) // ����
        {
            printf("\n���α׷��� �����մϴ�.\n");
            break;
        }
        else
        {
            printf("�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n");
        }
    }

    return 0;
}