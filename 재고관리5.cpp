//���θ� ������Ʈ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_NAME_LEN 50

int main()
{
    int product_number = MAX_PRODUCTS; // ��ǰ ���� ����
    int menu;

    // ��ǰ ���� �迭
    int product_stock_income[MAX_PRODUCTS + 1] = { 0 };
    int product_stock_sold[MAX_PRODUCTS + 1] = { 0 };
    int product_stock_current[MAX_PRODUCTS + 1] = { 0 };
    int product_price[MAX_PRODUCTS + 1] = { 0 };
    long long product_total_revenue[MAX_PRODUCTS + 1] = { 0 };
    char product_name[MAX_PRODUCTS + 1][MAX_NAME_LEN];

    // ��ǰ�� �⺻�� ����
    for (int i = 1; i <= MAX_PRODUCTS; i++) 
    {
        strcpy(product_name[i], "(���Է�)");
    }

    while (1) 
    {
        printf("\n���ϴ� �޴��� �����ϼ���.\n");
        printf("1. �԰�\n2. �Ǹ�\n3. ������ǰ����\n4. ��ü��Ȳ\n5. ����\n");
        printf("����: ");
        if (scanf("%d", &menu) != 1) 
        {
            printf("�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n");
            break;
        }

        // 1. �԰�
        if (menu == 1) 
        {
            int id, quantity, price;
            printf("\n<< �԰� �޴� ���� (��ǰID, ����, ���� �Է�) >>\n");
            printf("��ǰ ID�� �Է��ϼ��� (1 ~ %d): ", product_number);
            scanf("%d", &id);

            if (id < 1 || id > product_number) 
            {
                printf("�߸��� ��ǰ ID�Դϴ�.\n");
                continue;
            }
            if (strcmp(product_name[id], "(���Է�)") == 0) 
            {
                printf("��ǰ���� ��ϵ��� ���� ��ǰ�Դϴ�. ���� ��ǰ���� �Է��ϼ���.\n");
                continue;
            }

            printf("��ǰ��: %s\n", product_name[id]);
            printf("�԰� ����: ");
            scanf("%d", &quantity);
            printf("�Ǹ� ����: ");
            scanf("%d", &price);

            product_stock_income[id] += quantity;
            product_stock_current[id] += quantity;
            product_price[id] = price;

            printf("��ǰ ID %d (%s)�� %d�� �԰�, ����: %d��\n",
                id, product_name[id], quantity, price);
        }

        // 2. �Ǹ�
        else if (menu == 2) 
        {
            int id, quantity;
            printf("\n<< �Ǹ� �޴� ���� (��ǰID, �Ǹż��� �Է�) >>\n");
            printf("��ǰ ID�� �Է��ϼ��� (1 ~ %d): ", product_number);
            scanf("%d", &id);

            if (id < 1 || id > product_number) 
            {
                printf("�߸��� ��ǰ ID�Դϴ�.\n");
                continue;
            }
            if (strcmp(product_name[id], "(���Է�)") == 0)
            {
                printf("��ǰ���� ��ϵ��� ���� ��ǰ�Դϴ�. ���� ��ǰ���� �Է��ϼ���.\n");
                continue;
            }

            printf("��ǰ��: %s, ���� ���: %d\n", product_name[id], product_stock_current[id]);
            printf("�Ǹ� ����: ");
            scanf("%d", &quantity);

            if (quantity <= 0) 
            {
                printf("�Ǹ� ������ 1�� �̻��̾�� �մϴ�.\n");
                continue;
            }

            if (quantity > product_stock_current[id]) 
            {
                printf("��� ����! ���� ���: %d��\n", product_stock_current[id]);
                continue;
            }

            product_stock_sold[id] += quantity;
            product_stock_current[id] -= quantity;
            product_total_revenue[id] += (long long)quantity * product_price[id];

            printf("��ǰ ID %d (%s) %d�� �Ǹ�, �Ǹ� �ݾ�: %lld��\n",
                id, product_name[id], quantity, (long long)quantity * product_price[id]);

            if (product_stock_current[id] == 0) 
            {
                printf("�� ��� ����: ��ǰ ID %d (%s)\n", id, product_name[id]);
            }
        }

        // 3. ������ǰ����
        else if (menu == 3) 
        {
            int id, sub_menu;
            printf("\n<< ������ǰ���� >>\n");
            printf("1. ��ǰ�� �Է�/����\n2. ���� ��Ȳ ��ȸ\n����: ");
            scanf("%d", &sub_menu);

            printf("��ǰ ID�� �Է��ϼ��� (1 ~ %d): ", product_number);
            scanf("%d", &id);

            if (id < 1 || id > product_number) 
            {
                printf("�߸��� ��ǰ ID�Դϴ�.\n");
                continue;
            }

            if (sub_menu == 1) 
            {
                printf("�� ��ǰ�� �Է�: ");
                scanf("%s", product_name[id]);
                printf("��ǰ���� '%s'�� ��ϵǾ����ϴ�.\n", product_name[id]);
            }
            else if (sub_menu == 2) 
            {
                if (strcmp(product_name[id], "(���Է�)") == 0) 
                {
                    printf("��ǰ���� ���� ��ϵ��� �ʾҽ��ϴ�.\n");
                    continue;
                }
                printf("\n--- ��ǰ ID %d ��Ȳ ---\n", id);
                printf("��ǰ��        : %s\n", product_name[id]);
                printf("�Ǹ� ����     : %d ��\n", product_price[id]);
                printf("�԰� ����     : %d ��\n", product_stock_income[id]);
                printf("�Ǹ� ����     : %d ��\n", product_stock_sold[id]);
                printf("��� ����     : %d ��\n", product_stock_current[id]);
                printf("�� �Ǹ� �ݾ�  : %lld ��\n", product_total_revenue[id]);
            }
            else 
            {
                printf("�߸��� �����Դϴ�.\n");
            }
        }

        // 4. ��ü��Ȳ
        else if (menu == 4) 
        {
            printf("\n<< ��ü ��ǰ ��Ȳ >>\n");
            printf("��ǰID | ��ǰ��     | ��� | �԰� | �Ǹ� | ���� | ���Ǹűݾ�\n");
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
            printf("�� �԰�: %d, �� �Ǹŷ�: %d\n", total_income, total_sold);
            printf("�� �Ǹ���: %.2f%%\n", total_income > 0 ? (double)total_sold / total_income * 100 : 0.0);
            printf("�� �Ǹ� �ݾ�: %lld ��\n", overall_revenue);

            // �ִ�/�ּ� �Ǹ� ��ǰ
            int max_id = 1, min_id = 1;
            for (int i = 2; i <= product_number; i++) 
            {
                if (product_stock_sold[i] > product_stock_sold[max_id]) max_id = i;
                if (product_stock_sold[i] < product_stock_sold[min_id]) min_id = i;
            }

            printf("�ִ� �Ǹ� ��ǰ: ID %d (%s), �Ǹŷ� %d\n",
                max_id, product_name[max_id], product_stock_sold[max_id]);
            printf("�ּ� �Ǹ� ��ǰ: ID %d (%s), �Ǹŷ� %d\n",
                min_id, product_name[min_id], product_stock_sold[min_id]);

            // ��� ���� �˸�
            for (int i = 1; i <= product_number; i++) 
            {
                if (product_stock_current[i] <= 2) 
                {
                    printf("�� ��� ����: ��ǰ ID %d (%s), ���: %d��\n",
                        i, product_name[i], product_stock_current[i]);
                }
            }
        }

        // 5. ����
        else if (menu == 5) 
        {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }

        // �߸��� �Է�
        else 
        {
            printf("�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n");
        }
    }

    return 0;
}