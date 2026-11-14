# Roguelike на собственном движке (XYZ School, блок 4)

2D-рогалик на C++ и SFML 2.5.1 поверх компонентного движка `XYZEngine`, который пишется по ходу курса.
Репозиторий ведётся по домашним заданиям блока «Основы проектной разработки игр» и дипломному проекту.

![Арена с игроком и врагом](docs/screenshots/hw10-arena.png)

## Структура

| Проект | Что это |
|---|---|
| `XYZEngine` | статическая библиотека движка: `GameWorld`, `GameObject`, компоненты (`TransformComponent`, `SpriteRendererComponent`, `CameraComponent`, `InputComponent`, `RigidbodyComponent`, `SpriteColliderComponent`, `MovementComponent`, `SeekerComponent`, `AudioComponent`, `MusicComponent`, …), системы (`RenderSystem`, `PhysicsSystem`, `ResourceSystem`) |
| `XYZRoguelike` | сама игра: `GameMain.cpp`, сцена `DeveloperLevel`, контейнеры `Player`, `Enemy`, `Wall`, `Floor`, `Arena`, `Music`, настройки в `GameSettings.h` |
| `EngineTest` | unit-тесты движка на Google Test |
| `SFML` | библиотека SFML, подключается статически |

## Домашнее задание №10 — музыка, враг и стены

- **Звук в движке.** `ResourceSystem` научился загружать звуки (`LoadSound`/`GetSound`) и регистрировать музыкальные треки (`RegisterMusic`/`GetMusicPath`). `AudioComponent` проигрывает короткие звуки из памяти, `MusicComponent` стримит трек с диска. В движке только методы воспроизведения, конкретный файл выбирает игра.
- **Музыка.** Объект `Music` создаётся при старте уровня, включает трек `Resources/Music/theme.wav` и зацикливает его.
- **Игрок.** `MovementComponent` двигает объект по осям `InputComponent` (WASD), `SpriteMovementAnimationComponent` листает кадры карты текстур во время движения и разворачивает спрайт по направлению.
- **Враг.** `SeekerComponent` (движок) получает цель-трансформ, радиус обнаружения и скорость: пока игрок внутри радиуса — враг бежит к нему, вышел — враг останавливается. Контейнер `Enemy` собирает спрайт, твёрдое тело, коллайдер и этот компонент; цель — трансформ игрока.
- **Стены и пол.** `Arena` расставляет тайлы пола по сетке (без наложений) и кольцо стен по периметру. Пол создаётся раньше стен, поэтому рисуется под ними. `Wall` — кинематическое тело с коллайдером: физика выталкивает из него игрока и врага, а сама стена не сдвигается.

## Домашнее задание №11 — логирование, ассерты, здоровье и атака

- **Логгер.** `Logger` (движок) — единая точка входа с уровнями DEBUG / INFO / WARNING / ERROR и приёмниками `ConsoleSink` и `FileSink` (`log.txt` рядом с exe). Макросы `LOG_DEBUG("x=" << x)` и т.д. Все `std::cout` в движке заменены на логгер: создание и удаление объектов и коллайдеров — DEBUG, загрузка ресурсов, старт уровня, бой — INFO, подозрительные параметры и низкое здоровье — WARNING, отсутствующие ресурсы и неверное использование компонентов — ERROR.
- **Ассерты и исключения.** `ResourceSystem::LoadTextureMap` бросает `std::invalid_argument` при нулевом размере элемента, `RenderSystem::GetMainWindow` — `std::runtime_error` без окна, `Arena` — при неположительном размере; `GameMain` ловит их и пишет в лог. Ассерты стоят на нарушениях контракта (null-компонент, неположительное здоровье). Отсутствующая текстура не роняет игру: `ResourceSystem` пишет ERROR и подставляет ярко-розовую заглушку. Для демонстрации игра специально пытается загрузить несуществующий `Textures/Decor.png`.
- **Здоровье и броня.** `HealthComponent` (движок): максимум HP, броня вычитается из каждого удара (минимум 1 урона), колбэк смерти, WARNING при HP ниже 25 %. Игрок: 100 HP / 5 брони, враг: 50 HP / 2 брони.
- **Атака.** `AttackComponent` (движок): урон, дальность, перезарядка, `TryAttack(HealthComponent*)` и авто-режим `SetAutoTarget`. Враг бьёт игрока автоматически, когда догнал его. Игрок бьёт ближайшего врага в радиусе по пробелу (`PlayerCombatComponent` в игре, `InputComponent::IsAttackPressed`). Убитый враг удаляется из мира в конце кадра, смерть игрока перезапускает уровень через `GameWorld::RunLater`.

Фрагмент `log.txt`:

```
12:35:59.918 [INFO] 'Enemy' attacks 'Player' for 12
12:35:59.918 [INFO] 'Player' takes 7 damage from Enemy (12 minus 5 armour), health 93/100
12:36:01.081 [INFO] 'Player' attacks 'Enemy' for 20
12:36:01.085 [INFO] 'Enemy' takes 18 damage from Player (20 minus 2 armour), health 32/50
12:36:02.597 [INFO] 'Enemy' died
12:36:02.597 [INFO] Enemy defeated, removing it from the world
```

## Сборка и запуск

1. Открыть `Game.sln` в Visual Studio 2022 (toolset v143, C++17), собрать `XYZRoguelike` (x64).
2. Запускать из папки `XYZRoguelike/` — там лежат `Resources/`.
3. Управление: WASD — движение, пробел — удар, закрыть окно — выход.

```
msbuild Game.sln /t:XYZRoguelike /p:Configuration=Release /p:Platform=x64
```
