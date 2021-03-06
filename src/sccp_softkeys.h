/*!
 * \file        sccp_softkeys.h
 * \brief       SCCP SoftKeys Header
 * \author      Sergio Chersovani <mlists [at] c-net.it>
 * \note        Reworked, but based on chan_sccp code.
 *              The original chan_sccp driver that was made by Zozo which itself was derived from the chan_skinny driver.
 *              Modified by Jan Czmok and Julien Goodwin
 * \note        This program is free software and may be modified and distributed under the terms of the GNU Public License.
 *              See the LICENSE file at the top of the source tree.
 */
#pragma once
//#include "sccp_labels.h"

__BEGIN_C_EXTERN__
// forward declaration
extern const uint8_t softkeysmap[32];
SCCP_API struct softKeySetConfigList softKeySetConfig; /*!< List of SoftKeySets (impl sccp_softkey.c) */
typedef struct sccp_softkeyMap_cb sccp_softkeyMap_cb_t;

/*!
 * \brief SKINNY Soft Key Modes Structure
 */
typedef struct {
	uint8_t *ptr;												/*!< Point to next Mode */
	skinny_keymode_t id;												/*!< Soft Key ID */
	uint8_t count;												/*!< Soft Key Count */
} softkey_modes;												/*!< SKINNY Soft Key Modes Structure */

/*!
 * \brief SCCP SoftKeySet Configuration Structure
 */
struct softKeySetConfiguration {
	char name[SCCP_MAX_SOFTKEYSET_NAME];                  /*!< Name for this configuration */
	softkey_modes modes[SCCP_MAX_SOFTKEY_MODES];          /*!< SoftKeySet modes, see KEYMODE_ */
	sccp_softkeyMap_cb_t * softkeyCbMap;                  /*!< Softkey Callback Map, ie handlers */
	SCCP_LIST_ENTRY(sccp_softKeySetConfiguration_t) list; /*!< Next list entry */
	boolean_t pendingDelete;
	boolean_t pendingUpdate;
	uint8_t numberOfSoftKeySets;                                  /*!< Number of SoftKeySets we define */
};                                                                    /*!< SoftKeySet Configuration Structure */
SCCP_LIST_HEAD(softKeySetConfigList, sccp_softKeySetConfiguration_t); /*!< SCCP LIST HEAD for softKeySetConfigList (Structure) */

SCCP_API void SCCP_CALL sccp_softkey_pre_reload(void);
SCCP_API void SCCP_CALL sccp_softkey_post_reload(void);
SCCP_API void SCCP_CALL sccp_softkey_clear(void);

SCCP_API sccp_softkeyMap_cb_t * SCCP_CALL sccp_softkeyMap_copyStaticallyMapped(void);
SCCP_API boolean_t SCCP_CALL sccp_softkeyMap_replaceCallBackByUriAction(sccp_softkeyMap_cb_t * const softkeyMap, uint32_t event, char *uriactionstr);
SCCP_API boolean_t SCCP_CALL sccp_SoftkeyMap_execCallbackByEvent(devicePtr d, linePtr l, uint32_t lineInstance, channelPtr c, uint32_t event);
SCCP_API void SCCP_CALL sccp_softkey_setSoftkeyState(devicePtr device, skinny_keymode_t softKeySet, uint8_t softKey, boolean_t enable);
SCCP_API boolean_t __PURE__ SCCP_CALL sccp_softkey_isSoftkeyInSoftkeySet(constDevicePtr device, const skinny_keymode_t softKeySet, const uint8_t softKey);
__END_C_EXTERN__
// kate: indent-width 8; replace-tabs off; indent-mode cstyle; auto-insert-doxygen on; line-numbers on; tab-indents on; keep-extra-spaces off; auto-brackets off;
