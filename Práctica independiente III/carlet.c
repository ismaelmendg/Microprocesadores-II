void LCD_parse (char* letra, unsigned char caracter)
{
	switch (caracter){
	case 'a':
	letra[0] = 0x00;
	letra[1]=0xFC;
	letra[2] = 0x12;
	letra[3]=0x11;
	letra[4] = 0x12;
	letra[5]=0xFC;
	letra[6] = 0x00;

	break;

	case 'b':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x99;
	letra[3]=0x99;
	letra[4] = 0x99;
	letra[5]=0x66;
	letra[6] = 0x00;

	break;
	case 'c':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0xC3;
	letra[3]=0xC3;
	letra[4] = 0xC3;
	letra[5]=0xC3;
	letra[6] = 0x00;

	break;
	case 'd':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x81;
	letra[3]=0x81;
	letra[4] = 0x81;
	letra[5]=0x7E;
	letra[6] = 0x00;

	break;
	case 'e':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x99;
	letra[3]=0x99;
	letra[4] = 0x81;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case 'f':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x09;
	letra[3]=0x09;
	letra[4] = 0x01;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case 'g':
	letra[0] = 0x00;
	letra[1]=0x7E;
	letra[2] = 0x81;
	letra[3]=0x99;
	letra[4] = 0x99;
	letra[5]=0xF9;
	letra[6] = 0x00;

	break;

	case 'h':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x18;
	letra[3]=0x18;
	letra[4] = 0x18;
	letra[5]=0xFF;
	letra[6] = 0x00;

	break;
	case 'i':
	letra[0] = 0x00;
	letra[1]=0x81;
	letra[2] = 0x81;
	letra[3]=0xFF;
	letra[4] = 0x81;
	letra[5]=0x81;
	letra[6] = 0x00;

	break;
	case 'j':
	letra[0] = 0x00;
	letra[1]=0x71;
	letra[2] = 0xC1;
	letra[3]=0xC1;
	letra[4] = 0x7F;
	letra[5]=0x01;
	letra[6] = 0x00;

	break;
	case 'k':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x18;
	letra[3]=0x18;
	letra[4] = 0x24;
	letra[5]=0xC3;
	letra[6] = 0x00;

	break;
	case 'l':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x80;
	letra[3]=0x80;
	letra[4] = 0x80;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case 'm':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x06;
	letra[3]=0x0C;
	letra[4] = 0x06;
	letra[5]=0xFF;
	letra[6] = 0x00;

	break;
	case 'n':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0xF6;
	letra[3]=0x18;
	letra[4] = 0x60;
	letra[5]=0xFF;
	letra[6] = 0x00;

	break;

	case '_':
	letra[0] = 0x00;
	letra[1]=0xFC;
	letra[2] = 0x0D;
	letra[3]=0x19;
	letra[4] = 0x31;
	letra[5]=0xFC;
	letra[6] = 0x00;

	break;
	case 'o':
	letra[0] = 0x00;
	letra[1]=0x7E;
	letra[2] = 0xC3;
	letra[3]=0xC3;
	letra[4] = 0xC3;
	letra[5]=0x7E;
	letra[6] = 0x00;

	break;
	case 'p':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x0B;
	letra[3]=0x1B;
	letra[4] = 0x1B;
	letra[5]=0x0E;
	letra[6] = 0x00;

	break;
	case 'q':
	letra[0] = 0x00;
	letra[1]=0x7E;
	letra[2] = 0xC3;
	letra[3]=0xD3;
	letra[4] = 0x23;
	letra[5]=0x5E;
	letra[6] = 0x00;

	break;
	case 'r':
	letra[0] = 0x00;
	letra[1]=0xFF;
	letra[2] = 0x09;
	letra[3]=0x19;
	letra[4] = 0xE6;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case 's':
	letra[0] = 0x00;
	letra[1]=0x4E;
	letra[2] = 0x99;
	letra[3]=0x99;
	letra[4] = 0x99;
	letra[5]=0x72;
	letra[6] = 0x00;

	break;case 't':
	letra[0] = 0x00;
	letra[1]=0x01;
	letra[2] = 0x01;
	letra[3]=0xFF;
	letra[4] = 0x01;
	letra[5]=0x01;
	letra[6] = 0x00;

	break;case 'u':
	letra[0] = 0x00;
	letra[1]=0x7F;
	letra[2] = 0xC0;
	letra[3]=0xC0;
	letra[4] = 0xC0;
	letra[5]=0x7F;
	letra[6] = 0x00;

	break;case 'v':
	letra[0] = 0x00;
	letra[1]=0x3F;
	letra[2] = 0x60;
	letra[3]=0xC0;
	letra[4] = 0x60;
	letra[5]=0x3F;
	letra[6] = 0x00;

	break;case 'w':
	letra[0] = 0x00;
	letra[1]=0x7F;
	letra[2] = 0xC0;
	letra[3]=0xFE;
	letra[4] = 0xC0;
	letra[5]=0x7F;
	letra[6] = 0x00;

	break;case 'x':
	letra[0] = 0x00;
	letra[1]=0xC3;
	letra[2] = 0x24;
	letra[3]=0x18;
	letra[4] = 0x24;
	letra[5]=0xC3;
	letra[6] = 0x00;

	break;case 'y':
	letra[0] = 0x00;
	letra[1]=0x0F;
	letra[2] = 0x18;
	letra[3]=0xF0;
	letra[4] = 0x18;
	letra[5]=0x0F;
	letra[6] = 0x00;

	break;case 'z':
	letra[0] = 0x00;
	letra[1]=0xC1;
	letra[2] = 0xA1;
	letra[3]=0x91;
	letra[4] = 0x89;
	letra[5]=0x87;
	letra[6] = 0x00;

	break;case '0':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x7E;
	letra[3]=0xC3;
	letra[4] = 0x7E;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;case '1':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x82;
	letra[3]=0xFF;
	letra[4] = 0x80;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;case '2':
	letra[0] = 0x00;
	letra[1]=0xE2;
	letra[2] = 0xD1;
	letra[3]=0xC9;
	letra[4] = 0xC6;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;case '3':
	letra[0] = 0x00;
	letra[1]=0x42;
	letra[2] = 0xDB;
	letra[3]=0x99;
	letra[4] = 0xFF;
	letra[5]=0x42;
	letra[6] = 0x00;

	break;case '4':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x18;
	letra[3]=0x14;
	letra[4] = 0x12;
	letra[5]=0xFF;
	letra[6] = 0x00;

	break;case '5':
	letra[0] = 0x00;
	letra[1]=0x4F;
	letra[2] = 0x89;
	letra[3]=0x89;
	letra[4] = 0x89;
	letra[5]=0x71;
	letra[6] = 0x00;

	break;case '6':
	letra[0] = 0x00;
	letra[1]=0x7E;
	letra[2] = 0xD3;
	letra[3]=0x8B;
	letra[4] = 0xDB;
	letra[5]=0x62;
	letra[6] = 0x00;

	break;case '7':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x01;
	letra[3]=0xF1;
	letra[4] = 0x19;
	letra[5]=0x0F;
	letra[6] = 0x00;

	break;case '8':
	letra[0] = 0x00;
	letra[1]=0x66;
	letra[2] = 0xFF;
	letra[3]=0x99;
	letra[4] = 0xFF;
	letra[5]=0x66;
	letra[6] = 0x00;

	break;case '9':
	letra[0] = 0x00;
	letra[1]=0x4E;
	letra[2] = 0x9B;
	letra[3]=0x91;
	letra[4] = 0x9B;
	letra[5]=0x7E;
	letra[6] = 0x00;

	break;

	case '+':
	letra[0] = 0x00;
	letra[1]=0x18;
	letra[2] = 0x18;
	letra[3]=0xFF;
	letra[4] = 0x18;
	letra[5]=0x18;
	letra[6] = 0x00;

	break;
	case '-':
	letra[0] = 0x00;
	letra[1]=0x18;
	letra[2] = 0x18;
	letra[3]=0x18;
	letra[4] = 0x18;
	letra[5]=0x18;
	letra[6] = 0x00;

	break;
	case '*':
	letra[0] = 0x00;
	letra[1]=0xC3;
	letra[2] = 0x7E;
	letra[3]=0x18;
	letra[4] = 0x7E;
	letra[5]=0xC3;
	letra[6] = 0x00;

	break;
	case '/':
	letra[0] = 0x00;
	letra[1]=0x18;
	letra[2] = 0x18;
	letra[3]=0x5A;
	letra[4] = 0x18;
	letra[5]=0x18;
	letra[6] = 0x00;

	break;
	case '=':
	letra[0] = 0x00;
	letra[1]=0x66;
	letra[2] = 0x66;
	letra[3]=0x66;
	letra[4] = 0x66;
	letra[5]=0x66;
	letra[6] = 0x00;

	break;
	case '.':
	letra[0] = 0x00;
	letra[1]=0x60;
	letra[2] = 0x60;
	letra[3]=0x00;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case '(':
	letra[0] = 0x00;
	letra[1]=0x7E;
	letra[2] = 0x81;
	letra[3]=0x00;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case ')':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x00;
	letra[3]=0x00;
	letra[4] = 0x81;
	letra[5]=0x7E;
	letra[6] = 0x00;

	break;
	case '>':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x00;
	letra[3]=0x22;
	letra[4] = 0x14;
	letra[5]=0x08;
	letra[6] = 0x00;

	break;
	case '<':
	letra[0] = 0x00;
	letra[1]=0x08;
	letra[2] = 0x14;
	letra[3]=0x22;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case ':':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x00;
	letra[3]=0x66;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case '&':
	letra[0] = 0x00;
	letra[1]=0x60;
	letra[2] = 0x96;
	letra[3]=0x89;
	letra[4] = 0x96;
	letra[5]=0x60;
	letra[6] = 0x98;

	break;
	case ',':
	letra[0] = 0x00;
	letra[1]=0x1C;
	letra[2] = 0x3E;
	letra[3]=0xEC;
	letra[4] = 0x3E;
	letra[5]=0x1C;
	letra[6] = 0x00;

	break;
	case '{':
	letra[0] = 0x02;
	letra[1]=0x7E;
	letra[2] = 0x40;
	letra[3]=0x7E;
	letra[4] = 0x02;
	letra[5]=0x7E;
	letra[6] = 0x40;

	break;
	case '}':
	letra[0] = 0x40;
	letra[1]=0x7E;
	letra[2] = 0x02;
	letra[3]=0x7E;
	letra[4] = 0x40;
	letra[5]=0x7E;
	letra[6] = 0x02;

	break;
	case '|':
	letra[0] = 0xFF;
	letra[1]=0x00;
	letra[2] = 0x00;
	letra[3]=0x00;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;
	case '!':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x00;
	letra[3]=0x00;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0xFF;

	break;

	case ' ':
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x00;
	letra[3]=0x00;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0x00;

	break;

	default:
	letra[0] = 0x00;
	letra[1]=0x00;
	letra[2] = 0x00;
	letra[3]=0x00;
	letra[4] = 0x00;
	letra[5]=0x00;
	letra[6] = 0x00;
	break;
}}
