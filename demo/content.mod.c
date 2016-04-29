#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x96cec1da, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa0a77898, __VMLINUX_SYMBOL_STR(inet6_add_protocol) },
	{ 0xd9bf912, __VMLINUX_SYMBOL_STR(inet_sendmsg) },
	{ 0x9e9ef9dd, __VMLINUX_SYMBOL_STR(inet6_release) },
	{ 0x7c71e16b, __VMLINUX_SYMBOL_STR(inet6_register_protosw) },
	{ 0xf4b5bdf2, __VMLINUX_SYMBOL_STR(inet6_getname) },
	{ 0x42fec40, __VMLINUX_SYMBOL_STR(sk_common_release) },
	{ 0xf6a98d0c, __VMLINUX_SYMBOL_STR(sock_no_poll) },
	{ 0x94749e73, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0xd10ea92c, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xa980332c, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x6fe13ef, __VMLINUX_SYMBOL_STR(inet6_ioctl) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd2b47bf2, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x92644cb, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x32d3f498, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xc2c78033, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0x17c16b37, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0x65923edb, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xed63a7cc, __VMLINUX_SYMBOL_STR(ip6_route_output) },
	{ 0xc2234748, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0x461e6c85, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xc936e567, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x474720b4, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x8b81552f, __VMLINUX_SYMBOL_STR(inet6_del_protocol) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xb7906a68, __VMLINUX_SYMBOL_STR(sock_common_setsockopt) },
	{ 0x83f64406, __VMLINUX_SYMBOL_STR(sock_no_connect) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x6155b74d, __VMLINUX_SYMBOL_STR(sock_common_getsockopt) },
	{ 0x66c8ec65, __VMLINUX_SYMBOL_STR(inet6_unregister_protosw) },
	{ 0xc4d0ec1e, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x10026a50, __VMLINUX_SYMBOL_STR(inet_recvmsg) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A1DB892A60A0CB51D5DA4F9");
