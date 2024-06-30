#ifndef ENC28J60_EMAC_H_
#define ENC28J60_EMAC_H_

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "mbed.h"
#include "EMAC.h"
#include "rtos.h"

#include "utility/enc28j60.h"

#define ENC28J60_HWADDR_SIZE 6U

class ENC28J60EMAC : public EMAC {
public:
  ENC28J60EMAC(SPIClass& spi = SPI);

  static ENC28J60EMAC& get_instance(void);

  /**
   * Return maximum transmission unit
   *
   * @return     MTU in bytes
   */
  virtual uint32_t get_mtu_size(void) const;

  /**
   * Gets memory buffer alignment preference
   *
   * Gets preferred memory buffer alignment of the Emac device. IP stack may
   * or may not align link out memory buffer chains using the alignment.
   *
   * @return         Memory alignment requirement in bytes
   */
  virtual uint32_t get_align_preference(void) const;

  /**
   * Return interface name
   *
   * @param name Pointer to where the name should be written
   * @param size Maximum number of character to copy
   */
  virtual void get_ifname(char *name, uint8_t size) const;

  /**
   * Returns size of the underlying interface HW address size.
   *
   * @return     HW address size in bytes
   */
  virtual uint8_t get_hwaddr_size(void) const;

  /**
   * Return interface-supplied HW address
   *
   * Copies HW address to provided memory, @param addr has to be of correct
   * size see @a get_hwaddr_size
   *
   * HW address need not be provided if this interface does not have its own
   * HW address configuration; stack will choose address from central system
   * configuration if the function returns false and does not write to addr.
   *
   * @param addr HW address for underlying interface
   * @return     true if HW address is available
   */
  virtual bool get_hwaddr(uint8_t *addr) const;

  /**
   * Set HW address for interface
   *
   * Provided address has to be of correct size, see @a get_hwaddr_size
   *
   * Called to set the MAC address to actually use - if @a get_hwaddr is
   * provided the stack would normally use that, but it could be overridden,
   * eg for test purposes.
   *
   * @param addr Address to be set
   */
  virtual void set_hwaddr(const uint8_t *addr);

  /**
   * Initializes the HW
   *
   * @return True on success, False in case of an error.
   */
  virtual bool power_up(void);

  /**
   * Deinitializes the HW
   *
   */
  virtual void power_down(void);

  /**
   * Sends the packet over the link
   *
   * That can not be called from an interrupt context.
   *
   * @param buf  Packet to be send
   * @return     True if the packet was send successfully, False otherwise
   */
  virtual bool link_out(emac_mem_buf_t *buf);

  /**
   * Sets a callback that needs to be called for packets received for that
   * interface
   *
   * @param input_cb Function to be register as a callback
   */
  virtual void set_link_input_cb(emac_link_input_cb_t input_cb);

  /**
   * Sets a callback that needs to be called on link status changes for given
   * interface
   *
   * @param state_cb Function to be register as a callback
   */
  virtual void set_link_state_cb(emac_link_state_change_cb_t state_cb);

  /** Add device to a multicast group
   *
   * @param address  A multicast group hardware address
   */
  virtual void add_multicast_group(const uint8_t *address);

  /** Remove device from a multicast group
   *
   * @param address  A multicast group hardware address
   */
  virtual void remove_multicast_group(const uint8_t *address);

  /** Request reception of all multicast packets
   *
   * @param all True to receive all multicasts
   *            False to receive only multicasts addressed to specified groups
   */
  virtual void set_all_multicast(bool all);

  /** Sets memory manager that is used to handle memory buffers
   *
   * @param mem_mngr Pointer to memory manager
   */
  virtual void set_memory_manager(EMACMemoryManager &mem_mngr);

private:
  void receiveTask();
  void linkStatusTask();

  SPIClass& spi;
  ENC28J60 driver;
  uint8_t macAddr[ENC28J60_HWADDR_SIZE];

  int receiveTaskHandle = 0;
  int linkStatusTaskHandle = 0;

  EMACMemoryManager* memoryManager = nullptr;
  rtos::Mutex ethLockMutex;

  emac_link_input_cb_t emac_link_input_cb;
  emac_link_state_change_cb_t emac_link_state_cb;
};

#endif
