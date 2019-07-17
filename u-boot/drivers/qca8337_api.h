/*  Copyright(c) 2003-2017 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		qca8337_api.h
 * brief		
 * details	
 *
 * author		WANG Wenhu
 * version	
 * date		Dec31th 2016
 *
 * history 	\arg	
 */
#ifndef __QCA8337_API_H__
#define __QCA8337_API_H__

#include <common.h>

/**************************************************************************************************/
/*                                           DEFINES                                              */
/**************************************************************************************************/

/* ACL Registers */
#define S17_ACL_FUNC0_REG               0x0400
#define S17_ACL_FUNC1_REG               0x0404
#define S17_ACL_FUNC2_REG               0x0408
#define S17_ACL_FUNC3_REG               0x040c
#define S17_ACL_FUNC4_REG               0x0410
#define S17_ACL_FUNC5_REG               0x0414
#define S17_PRIVATE_IP_REG              0x0418
#define S17_P0VLAN_CTRL0_REG            0x0420
#define S17_P0VLAN_CTRL1_REG            0x0424
#define S17_P1VLAN_CTRL0_REG            0x0428
#define S17_P1VLAN_CTRL1_REG            0x042c
#define S17_P2VLAN_CTRL0_REG            0x0430
#define S17_P2VLAN_CTRL1_REG            0x0434
#define S17_P3VLAN_CTRL0_REG            0x0438
#define S17_P3VLAN_CTRL1_REG            0x043c
#define S17_P4VLAN_CTRL0_REG            0x0440
#define S17_P4VLAN_CTRL1_REG            0x0444
#define S17_P5VLAN_CTRL0_REG            0x0448
#define S17_P5VLAN_CTRL1_REG            0x044c
#define S17_P6VLAN_CTRL0_REG            0x0450
#define S17_P6VLAN_CTRL1_REG            0x0454 

/* Table Lookup Registers */
#define S17_ATU_DATA0_REG               0x0600
#define S17_ATU_DATA1_REG               0x0604
#define S17_ATU_DATA2_REG               0x0608
#define S17_ATU_FUNC_REG                0x060C
#define S17_VTU_FUNC0_REG               0x0610
#define S17_VTU_FUNC1_REG               0x0614
#define S17_ARL_CTRL_REG                0x0618
#define S17_GLOFW_CTRL0_REG             0x0620
#define S17_GLOFW_CTRL1_REG             0x0624
#define S17_GLOLEARN_LIMIT_REG          0x0628
#define S17_TOS_PRIMAP_REG0             0x0630
#define S17_TOS_PRIMAP_REG1             0x0634
#define S17_TOS_PRIMAP_REG2             0x0638
#define S17_TOS_PRIMAP_REG3             0x063c
#define S17_TOS_PRIMAP_REG4             0x0640
#define S17_TOS_PRIMAP_REG5             0x0644
#define S17_TOS_PRIMAP_REG6             0x0648
#define S17_TOS_PRIMAP_REG7             0x064c
#define S17_VLAN_PRIMAP_REG0            0x0650
#define S17_LOOP_CHECK_REG              0x0654
#define S17_P0LOOKUP_CTRL_REG           0x0660
#define S17_P0PRI_CTRL_REG              0x0664
#define S17_P0LEARN_LMT_REG             0x0668
#define S17_P1LOOKUP_CTRL_REG           0x066c
#define S17_P1PRI_CTRL_REG              0x0670
#define S17_P1LEARN_LMT_REG             0x0674
#define S17_P2LOOKUP_CTRL_REG           0x0678
#define S17_P2PRI_CTRL_REG              0x067c
#define S17_P2LEARN_LMT_REG             0x0680
#define S17_P3LOOKUP_CTRL_REG           0x0684
#define S17_P3PRI_CTRL_REG              0x0688
#define S17_P3LEARN_LMT_REG             0x068c
#define S17_P4LOOKUP_CTRL_REG           0x0690
#define S17_P4PRI_CTRL_REG              0x0694
#define S17_P4LEARN_LMT_REG             0x0698
#define S17_P5LOOKUP_CTRL_REG           0x069c
#define S17_P5PRI_CTRL_REG              0x06a0
#define S17_P5LEARN_LMT_REG             0x06a4
#define S17_P6LOOKUP_CTRL_REG           0x06a8
#define S17_P6PRI_CTRL_REG              0x06ac
#define S17_P6LEARN_LMT_REG             0x06b0
#define S17_GLO_TRUNK_CTRL0_REG         0x0700
#define S17_GLO_TRUNK_CTRL1_REG         0x0704
#define S17_GLO_TRUNK_CTRL2_REG         0x0708

#define S17_MASK_CTRL_REG               0x0000
#define S17_P0PAD_MODE_REG              0x0004
#define S17_P5PAD_MODE_REG              0x0008
#define S17_P6PAD_MODE_REG              0x000c
#define S17_PWS_REG                     0x0010


#define S17_P0STATUS_REG                0x007c
#define S17_P1STATUS_REG                0x0080
#define S17_P2STATUS_REG                0x0084
#define S17_P3STATUS_REG                0x0088
#define S17_P4STATUS_REG                0x008c
#define S17_P5STATUS_REG                0x0090
#define S17_P6STATUS_REG                0x0094
#define S17_SGMII_CTRL_REG              0x00e0

#define S17_MAC0_MAC_MII_RXCLK_SEL	(1 << 0)
#define S17_MAC0_MAC_MII_TXCLK_SEL	(1 << 1)
#define S17_MAC0_MAC_MII_EN		(1 << 2)
#define S17_MAC0_MAC_GMII_RXCLK_SEL	(1 << 4)
#define S17_MAC0_MAC_GMII_TXCLK_SEL	(1 << 5)
#define S17_MAC0_MAC_GMII_EN		(1 << 6)
#define S17_MAC0_SGMII_EN		(1 << 7)
#define S17_MAC0_PHY_MII_RXCLK_SEL	(1 << 8)
#define S17_MAC0_PHY_MII_TXCLK_SEL	(1 << 9)
#define S17_MAC0_PHY_MII_EN		(1 << 10)
#define S17_MAC0_PHY_MII_PIPE_SEL	(1 << 11)
#define S17_MAC0_PHY_GMII_RXCLK_SEL	(1 << 12)
#define S17_MAC0_PHY_GMII_TXCLK_SEL	(1 << 13)
#define S17_MAC0_PHY_GMII_EN		(1 << 14)
#define S17_MAC0_RGMII_RXCLK_SHIFT	20
#define S17_MAC0_RGMII_TXCLK_SHIFT	22
#define S17_MAC0_RGMII_RXCLK_DELAY	(1 << 24)
#define S17_MAC0_RGMII_TXCLK_DELAY	(1 << 25)
#define S17_MAC0_RGMII_EN		(1 << 26)

#define S17_MAC5_MAC_MII_RXCLK_SEL	(1 << 0)
#define S17_MAC5_MAC_MII_TXCLK_SEL	(1 << 1)
#define S17_MAC5_MAC_MII_EN		(1 << 2)
#define S17_MAC5_PHY_MII_RXCLK_SEL	(1 << 8)
#define S17_MAC5_PHY_MII_TXCLK_SEL	(1 << 9)
#define S17_MAC5_PHY_MII_EN		(1 << 10)
#define S17_MAC5_PHY_MII_PIPE_SEL	(1 << 11)
#define S17_MAC5_RGMII_RXCLK_SHIFT	20
#define S17_MAC5_RGMII_TXCLK_SHIFT	22
#define S17_MAC5_RGMII_RXCLK_DELAY	(1 << 24)
#define S17_MAC5_RGMII_TXCLK_DELAY	(1 << 25)
#define S17_MAC5_RGMII_EN		(1 << 26)

#define S17_MAC6_MAC_MII_RXCLK_SEL	(1 << 0)
#define S17_MAC6_MAC_MII_TXCLK_SEL	(1 << 1)
#define S17_MAC6_MAC_MII_EN		(1 << 2)
#define S17_MAC6_MAC_GMII_RXCLK_SEL	(1 << 4)
#define S17_MAC6_MAC_GMII_TXCLK_SEL	(1 << 5)
#define S17_MAC6_MAC_GMII_EN		(1 << 6)
#define S17_MAC6_SGMII_EN		(1 << 7)
#define S17_MAC6_PHY_MII_RXCLK_SEL	(1 << 8)
#define S17_MAC6_PHY_MII_TXCLK_SEL	(1 << 9)
#define S17_MAC6_PHY_MII_EN		(1 << 10)
#define S17_MAC6_PHY_MII_PIPE_SEL	(1 << 11)
#define S17_MAC6_PHY_GMII_RXCLK_SEL	(1 << 12)
#define S17_MAC6_PHY_GMII_TXCLK_SEL	(1 << 13)
#define S17_MAC6_PHY_GMII_EN		(1 << 14)
#define S17_PHY4_GMII_EN		(1 << 16)
#define S17_PHY4_RGMII_EN		(1 << 17)
#define S17_PHY4_MII_EN			(1 << 18)
#define S17_MAC6_RGMII_RXCLK_SHIFT	20
#define S17_MAC6_RGMII_TXCLK_SHIFT	22
#define S17_MAC6_RGMII_RXCLK_DELAY	(1 << 24)
#define S17_MAC6_RGMII_TXCLK_DELAY	(1 << 25)
#define S17_MAC6_RGMII_EN		(1 << 26)

#define S17_SPEED_10M			(0 << 0)
#define S17_SPEED_100M			(1 << 0)
#define S17_SPEED_1000M			(2 << 0)
#define S17_TXMAC_EN			(1 << 2)
#define S17_RXMAC_EN			(1 << 3)
#define S17_TX_FLOW_EN			(1 << 4)
#define S17_RX_FLOW_EN			(1 << 5)
#define S17_DUPLEX_FULL			(1 << 6)
#define S17_DUPLEX_HALF			(0 << 6)
#define S17_TX_HALF_FLOW_EN		(1 << 7)
#define S17_LINK_EN				(1 << 9)
#define S17_FLOW_LINK_EN		(1 << 12)
#define S17_PORT_STATUS_DEFAULT		(S17_SPEED_1000M | S17_TXMAC_EN | \
                                        S17_RXMAC_EN | S17_TX_FLOW_EN | \
                                        S17_RX_FLOW_EN | S17_DUPLEX_FULL | \
                                        S17_TX_HALF_FLOW_EN)

#define S17_PORT_STATUS_AZ_DEFAULT	(S17_SPEED_1000M | S17_TXMAC_EN | \
                                        S17_RXMAC_EN | S17_TX_FLOW_EN | \
                                        S17_RX_FLOW_EN | S17_DUPLEX_FULL)


#define REG_VALUE_EN 				(S17_MAC0_RGMII_EN | S17_MAC0_RGMII_TXCLK_DELAY | S17_MAC0_RGMII_RXCLK_DELAY)

/* MDC/MDIO related fields. */
#define QCA_REG_OFFSET_TO_MDIO_PHY_ADDR(reg)		(((reg >> 6) & 0x7)  | (0x2 << 3))
#define QCA_REG_OFFSET_TO_MDIO_REG_ADDR_HIGH(reg)	(((reg >> 1) & 0x1e) | 0x1)
#define QCA_REG_OFFSET_TO_MDIO_REG_ADDR_LOW(reg) 	((reg >> 1) & 0x1e)
#define QCA_REG_OFFSET_TO_MDIO_DATA(reg)			((reg >> 9) & 0x3ff)
#define QCA_WRITE_HIGH_ADDR_MDIO_PHY_ADDR			(0x3 << 3)
#define QCA_WRITE_HIGH_ADDR_MDIO_REG_ADDR			(0x0)

/**************************************************************************************************/
/*                                           TYPES                                                */
/**************************************************************************************************/



/**************************************************************************************************/
/*                                           VARIABLES                                            */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                           FUNCTIONS                                            */
/**************************************************************************************************/

void sleep(u32 time);

void qca8337_init();
u32 qca8337_read_register(u32 reg, u32* data);
u32 qca8337_write_register(u32 reg, u32 data);
void qca8337_vlan_config();
void qca8337_reset();

#endif /* __QCA8337_API_H__ */ 

