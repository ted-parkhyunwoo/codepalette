#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	srand(time(NULL));
	printf("\n\n === ŸÆºüŽÂ ŽëžÓž® °ÔÀÓ === \n\n");
	int answer; // »ç¿ëÀÚ ÀÔ·Â°ª
	int treatment = rand() % 4; // ¹ßžðÁŠ Œ±ÅÃ (0~3)

	int cntShowBottle = 0; // ÀÌ¹ø °ÔÀÓ¿¡ ºž¿©ÁÙ ºŽ °¹Œö
	int prevCntShowBottle = 0; // ŸÕ °ÔÀÓ¿¡ ºž¿©ÁØ ºŽ °¹Œö
	// Œ­·Î ºž¿©ÁÖŽÂ ºŽ °¹ŒöžŠ ŽÙž£°Ô ÇÏ¿© Á€Žä·ü Çâ»ó (Ã³Àœ¿¡ 2°³ -> ŽÙÀœ¿£ 3°³ ..)

	// 3¹øÀÇ ±âÈž (3¹øÀÇ ¹ßžðÁŠ Åõ¿© œÃµµ)
	for (int i = 1; i <= 3; i++)
	{
		int bottle[4] = { 0, 0, 0, 0 }; // 4°³ÀÇ ºŽ
		do {
			cntShowBottle = rand() % 2 + 2; // ºž¿©ÁÙ ºŽ °¹Œö (0~1, +2 -> 2, 3)
		} while (cntShowBottle == prevCntShowBottle);
		prevCntShowBottle = cntShowBottle;

		int isIncluded = 0; // ºž¿©ÁÙ ºŽ Áß¿¡ ¹ßžðÁŠ°¡ Æ÷ÇÔµÇŸúŽÂÁö ¿©ºÎ (1 : Æ÷ÇÔ)
		printf(" > %d ¹øÂ° œÃµµ : ", i);

		// ºž¿©ÁÙ ºŽ ÁŸ·ùžŠ Œ±ÅÃ
		for (int j = 0; j < cntShowBottle; j++)
		{
			int randBottle = rand() % 4; // 0~3

			// ŸÆÁ÷ Œ±ÅÃµÇÁö ŸÊÀº ºŽÀÌžé, Œ±ÅÃ Ã³ž®
			if (bottle[randBottle] == 0)
			{
				bottle[randBottle] = 1;
				if (randBottle == treatment)
				{
					isIncluded = 1;
				}
			}
			// ÀÌ¹Ì Œ±ÅÃµÈ ºŽÀÌžé, Áßº¹ÀÌ¹Ç·Î ŽÙœÃ Œ±ÅÃ
			else
			{
				j--;
			}
		}

		// »ç¿ëÀÚ¿¡°Ô ¹®ÁŠ Ç¥œÃ
		for (int k = 0; k < 4; k++)
		{
			if (bottle[k] == 1)
				printf("%d ", k + 1);
		}
		printf(" ¹°ŸàÀ» žÓž®¿¡ ¹ÙžšŽÏŽÙ\n\n");

		if (isIncluded == 1)
		{
			printf("  >> Œº°ø ! žÓž®°¡ ³µŸî¿ä !!\n");
		}
		else
		{
			printf("  >> œÇÆÐ ! žÓž®°¡ ³ªÁö ŸÊŸÒŸî¿ä.. €Ð€Ð\n");
		}

		printf("\n ... °èŒÓ ÇÏ·Ážé ŸÆ¹«Å°³ª Ž©ž£ŒŒ¿ä ...");
		getchar();
	}

	printf("\n\n¹ßžðÁŠŽÂ žî ¹øÀÏ±î¿ä? ");
	scanf("%d", &answer);

	if (answer == treatment + 1)
	{
		printf("\n >> Á€ŽäÀÔŽÏŽÙ!\n");
	}
	else
	{
		printf("\n >> ¶¯ ! Æ²·ÈŸî¿ä, Á€ŽäÀº %d ÀÔŽÏŽÙ\n", treatment + 1);
	}

	return 0;
}
