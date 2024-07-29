# DMAByDaylight
这是一个Fork已有的面向DMA开发的黎明杀机外部纯读辅助。仅供学习，不可商用。

> [!WARNING]
> 
>This project is intended solely for educational and research purposes. Any commercial use of this project is strictly prohibited. The author is not responsible for any legal consequences arising from the commercial use of this project.
> 

> [!WARNING]
> 
>本项目仅供学习和研究使用，任何商业化用途均被严格禁止，包括但不限于二次封装发售，增加发卡系统，商业倒卖，包更新等。因商业化使用本项目而导致的任何法律后果，作者不承担任何责任。淘宝，闲鱼，京东等电商平台的有关商品和本人没有任何关系，也不存在授权行为，本软件遵守MIT Linence。
> 


## Showcase
![image](https://github.com/user-attachments/assets/db509731-e929-4be0-82e8-e063dd49927e)
<br>
<img width="1415" alt="0f33b5dd4d31d3c020211dc0cea47c7" src="https://github.com/user-attachments/assets/70a9b997-c0a1-40b0-82a9-08251e5509fb">

## Instructions
* [Installation Guide](./Instructions.md)
<br>

如果你想更新，请通过 [Dumper-7](https://github.com/Encryqed/Dumper-7) 来dump数据，具体的做法是：下载并编译dll文件，使用CE的注入DLL功能进行dump，然后找到Basic.cpp文件，比对GWorld，Level等关键数据的偏移。或者，在这个项目下发布一个issue，我看到就会更新。


## 功能
* Survivor ESP
  * Name（原作者并没有区分角色名称，全都展示Survivor，我做了优化现在会展示具体名称，例如尼亚）
  * Distance
  * Font Size
  * Max Distance
* Killer ESP（和Survivor一样会展示具体角色名，例如护士）
  * Name
  * Distance
  * Font Size
  * Max Distance
    <br>
  <b>-----以上为原作者已实现的功能，我站在巨人的肩膀上新实现了一些小东西：------</b>
    <br>
* 大门透视(Exit Gate)
  * Name
  * Distance
  * Font Size
  * Max Distance
* 地窖透视(Hatch)
  * Name
  * Distance
  * Font Size
  * Max Distance
* 板子透视(Pallet)
  * Name
  * Distance
  * Font Size
  * Max Distance
  * Custom W2S Resolution
* 发电机透视（Generator）
  * Name
  * Distance
  * Font Size
  * Max Distance
  * current process percent(当前已修进度)
* 杀手道具透视（Killer Items，目前只实现了夹哥的trap ESP）
  * Name
  * Distance
  * Font Size
  * Max Distance
* Debug模式（慎用，极大影响性能）
  * 开启这个功能会展示游戏里所有对象的实时内存地址和对应的Actor-Uclass-FNameID，方便调试
![image](https://github.com/user-attachments/assets/5acb3315-bfa3-4d3a-8ec6-44b649f565ad)
 
## Update Plan（更新计划）
* 我正在实现护士的落点透视（就像护士带方格布的那种效果）。<br>
![trim FFA91CA8-B7BE-48B9-ACE7-0C051361E2A6](https://github.com/user-attachments/assets/6eeaf329-2a8d-4855-a465-3572f7790adc)
* 图腾的ESP正在跟进中，正在映射技能名。
* 未来考虑增加板子的状态，例如可用，或者已被放下。
* 考虑加入窗户的ESP。
* 人物的挂钩次数已排进日程，目前还没找到关联数据
* 自瞄功能已经排进日程，方便追追，兔妈，异形等屠夫使用。
 
## 关于自瞄的一些看法
实战发现绝大多数中长手屠夫的有效技能长度不超过16m。考虑到黎明杀机这款游戏不存在爆头这个概念，即击中任意部位都算做一次同样的伤害，所以瞄准上胸能尽可能的增加命中率。

* 枪手：16m。但超过10m散布很大
* 追追：一阶段3m，二阶段6m，三阶段7-8m
* 护士：一飞大概22m左右的飞行距离
* 兔妈：无限，但实战基本在16m内
* 威斯克：一冲6-10m，二冲15-25m
* 只云哥哥：无限，但因为有较大散布，所以10m内最佳
* 异形：6m，但考虑网络延迟，用技能时不要超过5m
* 自动QTE之后再加，包括扳机和自动下板，我得先学KMBOX的调用，你也可以留言给我个例子，不胜感谢！


## Credits

* [DMAByDaylight](https://github.com/IntelSDM/DMAByDaylight)(本项目的原作者，感谢其搭建的基础框架和封装的读写函数 I would like to thank the original author of this project for setting up the foundational framework and encapsulating the read/write functions.)
* [DBDHunter](https://github.com/lihaochen910/DBDHunter)(非常感谢在我开发过程中给予我极大帮助的大佬，使得我可以顺利开发功能)
* [PCILeech](https://github.com/ufrisk/pcileech)
* [MemProcFS](https://github.com/ufrisk/MemProcFS)
* [UnnamedZ03](https://github.com/UnnamedZ03/DBD-external-base)
* [DMALibrary](https://github.com/Metick/DMALibrary/tree/Master)

