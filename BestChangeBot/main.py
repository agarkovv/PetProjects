import logging
import aiogram.utils.markdown as md
from aiogram import Bot, Dispatcher, types
from aiogram.contrib.fsm_storage.memory import MemoryStorage
from aiogram.dispatcher import FSMContext
from aiogram.dispatcher.filters import Text
from aiogram.dispatcher.filters.state import State, StatesGroup
from aiogram.types import ParseMode
from aiogram.utils import executor

from parser import BestChange

import configparser

config = configparser.ConfigParser()
config.read("settings.ini")

bot = Bot(token=config["Bot"]["token"], parse_mode=config["Bot"]["parse_mode"])
storage = MemoryStorage()
dp = Dispatcher(bot, storage=storage)

# Запуск парсера
api = BestChange(cache_seconds=3600, exchangers_reviews=True, split_reviews=True)
currencies = api.currencies().get()
exchangers = api.exchangers().get()


class Transaction(StatesGroup):
    str_from = State()
    str_to = State()
    how_many = State()


# Приветствие, типовые команды.
# Переключаем пользователя на общение в ЛС
@dp.message_handler(commands=['start'])
async def command_start(message: types.Message):
    try:
        await bot.send_message(message.from_user.id,
                               '<b>🤖 Hi! \nI`ll help you to exchange your coins on BestChange!</b>')
        await bot.send_message(message.from_user.id,
                               'Write /help to see all commands')
        await message.delete()
    except:
        await message.reply('<b>Don`t let other know your private information!</b>'
                            '\n\nText me private message:'
                            '\nhttps://t.me/BestChangePythonBot')

@dp.message_handler(commands=['help'])
async def command_start(message: types.Message):
    await bot.send_message(message.from_user.id, '<em>BOT COMMANDS:</em>'
                                                 '\n👷 /start - to start or restart bot\n'
                                                 '🥷 /help - to see all commands\n'
                                                 '💂 /cancel - go back\n'
                                                 '🎎 /exchange - to exchange your wallet from one to another\n')


@dp.message_handler(commands=['exchange'])
async def command_exchange(message: types.Message):
    await Transaction.str_from.set()
    await bot.send_message(message.from_user.id, 'Enter <em>Wallet</em> to exchange')


@dp.message_handler(state='*', commands='cancel')
@dp.message_handler(Text(equals='cancel', ignore_case=True), state='*')
async def cancel_handler(message: types.Message, state: FSMContext):
    """
    Allow user to cancel any action
    """
    current_state = await state.get_state()
    if current_state is None:
        return

    logging.info('Cancelling state %r', current_state)
    # Cancel state and inform user about it
    await state.finish()
    # And remove keyboard (just in case)
    await message.reply('Cancelled.', reply_markup=types.ReplyKeyboardRemove())


@dp.message_handler(state=Transaction.str_from)
async def process_exchange(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['str_from'] = message.text

    await Transaction.next()
    await bot.send_message(message.from_user.id, 'Enter <em>Wallet</em> to exchange <em>ON</em>')


@dp.message_handler(state=Transaction.str_to)
async def process_exchange2(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['str_to'] = message.text

    await Transaction.next()
    await bot.send_message(message.from_user.id, 'Enter <em>Sum</em> that you want to exchange')


@dp.message_handler(state=Transaction.how_many)
async def process_exchange3(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['how_many'] = int(message.text)

    await bot.send_message(message.from_user.id, '<b>Processing...</b>'
                                                 '\n\nPlease wait'
                                                 '\nBot is searching the most profitable exchange!')

    dir_from = api.currencies().search_by_name(data['str_from'])
    dir_to = api.currencies().search_by_name(data['str_to'])

    id_from = -1
    for key in dir_from:
        id_from = dir_from[key]['id']
        break

    id_to = -1
    for key in dir_to:
        id_to = dir_to[key]['id']
        break

    rows = api.rates().filter(id_from, id_to)
    title = 'Exchange rates in the direction (' + config["Bot"]["token"] + '={}&to={}) {} : {}'
    await bot.send_message(message.from_user.id, (title.format(id_from, id_to, data['str_from'], data['str_to'])))
    limit = 5
    for val in rows:
        if limit == 0:
            break
        if val['min_sum'] < data['how_many'] < val['max_sum']:
            await bot.send_message(message.from_user.id, ('{} {}'.format('🔥', exchangers[val['exchange_id']]['name'])))
            await bot.send_message(message.from_user.id, ('{} {} {}'.format('<b>YOU GIVE:</b>', val['give'] * data['how_many'], data['str_from'])))
            await bot.send_message(message.from_user.id, ('{} {} {}'.format('<b>YOU GET:</b>', val['get'] * data['how_many'], data['str_to'])))
            await bot.send_message(message.from_user.id, ('{} {}'.format('<b>GOOD FEEDBACK REVIEWS</b>:', val['reviews'][1])))
            limit -= 1

    await state.finish()


@dp.message_handler()
async def echo_send(message: types.Message):
    await message.answer(message.text)  # Оправить сообщение
    # await message.reply(message.text)  # Ответить
    # await bot.send_message(message.from_user.id, message.text)


def main():
    executor.start_polling(dp, skip_updates=True)  # Бот не отвечает на нерелевантные сообщения

if __name__ == '__main__':
    main()