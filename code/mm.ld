OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS{

	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
	}

	.patch_startHeap 0x010001C : {
		*(.patch_startHeap)
	}

	.patch_MainLoop 0x10676C : {
		*(.patch_MainLoop)
	}

	.patch_DecoupleZlZr 0x1166C8 :  {
		*(.patch_DecoupleZlZr)
	}

	.patch_DecoupleStartSelect 0x121EE8 : {
		*(.patch_DecoupleStartSelect)
	}

	.patch_SpawnFastElegyStatues 0x1E9FB8 : {
		*(.patch_SpawnFastElegyStatues)
	}

	.patch_UseZoraASwimSecond 0X1FFD74 : {
		*(.patch_UseZoraASwimSecond)
	}

	.patch_ThirdZoraSwimCheck 0x1FFDBC : {
		*(.patch_ThirdZoraSwimCheck)
	}

	.patch_UseZoraASwimFirst 0x220EFC : {
		*(.patch_UseZoraASwimFirst)
	}

	.patch_FirstZoraSwimCheck 0x220F60 : {
		*(.patch_FirstZoraSwimCheck)
	}

	.patch_SecondZoraSwimCheck 0x2210DC : {
		*(.patch_SecondZoraSwimCheck)
	}

	/*TODO: Find a better place for this function call. This is called almost every frame during file selection but it works?*/
	.patch_SaveFile_init 0x5BB44C : {
		*(.patch_SaveFile_init)
	}

	.patch_FixSurroundSound 0x1404E8 : {
		*(.patch_FixSurroundSound)
	}

	.patch_OcarinaDive 0x1E1F0C : {
		*(.patch_OcarinaDive)
	}

	.patch_GetCustomText 0x1BDE78 : {
		*(.patch_GetCustomText)
	}

	.patch_ISGCrouchStabOne 0x1D32E0 : {
		*(.patch_ISGCrouchStabOne)
	}

	.patch_ISGCrouchStabTwo 0x1DBEA4 : {
		*(.patch_ISGCrouchStabTwo)
	}

	.patch_RemoveRemainsStateCheck 0x22B7BC : {
			*(.patch_RemoveRemainsStateCheck)
	}

	.patch_ChangeDrawItemIndex 0x22F24C : { 
		*(.patch_ChangeDrawItemIndex)
	}

	.patch_ChangeDrawItemIndexSecond 0x22F474 : { 
		*(.patch_ChangeDrawItemIndexSecond)
	}	

	.patch_OverrideTextID 0x2310FC : {
		*(.patch_OverrideTextID)
	}

	.patch_OverrideItemID 0x231108 : {
		*(.patch_OverrideItemID)
	}

	.patch_TwinmoldConsistentDamage 0x28E544 : {
		*(.patch_TwinmoldConsistentDamage)
	}

	.patch_FasterBlockMovement 0x2AC634 : {
		*(.patch_FasterBlockMovement)
	}

	.patch_FasterBlockMovementBack 0x2D0C0C : {
		*(.patch_FasterBlockMovementBack)
	}

	.patch_IncomingGetItemID 0x4B1394 : {
		*(.patch_IncomingGetItemID)
	}

	.patch_ReadGamePad 0x59BA10 : {
		*(.patch_ReadGamePad)
	}

	.patch_DisableExistingTrigger 0x59BA14 : {
		*(.patch_DisableExistingTrigger)
	}

	.patch_ItemCloseOnSelect 0x5C19E4 : {
		*(.patch_ItemCloseOnSelect)
	}

	.patch_HandleOcarinaHooks 0x604D8C : {
		*(.patch_HandleOcarinaHooks)
	}

	. = 0x61CD8C;
	/* Addr already 4 byte aligned! */
	/* . = ALIGN(4); */
	.loader : {
		*(.loader*)
	}

    . = 0x007D0000;
    .text : {
        __text_start = . ;
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.data)
        *(.bss)
        *(COMMON)
        __text_end  = . ;
    }
}